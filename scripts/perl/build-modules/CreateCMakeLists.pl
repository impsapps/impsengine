#!/usr/bin/perl

package BuildAndroidModule;

use strict;
use warnings;

BEGIN {push @INC, '.'}

use Cwd;
use BuildModuleHelper;
use Module;


sub addSrcFiles {
    my $srcFiles = shift;
    my $filePath = shift;
    
    opendir(DH, $filePath) or die "Could not open $filePath. Reason: $!";
    my @names = readdir(DH);
    closedir(DH);
    
    foreach my $name (@names){
        my $newName = $filePath . '/' . $name;
        if(-f $newName){
            if ($newName =~ m/\.c$/){
                push @{$srcFiles}, $newName;
            }
        }elsif(-d $newName and not $name =~ m/^\./){
            addSrcFiles($srcFiles, $newName);
        }
    }
}


my $modules = getHashMapReferenceToAllModules();

my @srcDirs;
my @includeDirs;

foreach my $module (values %$modules){
    my $includeDir = $module->getAndroidIncludeFolder();
    my $relativeIncludeDir = getPathRelativeToRootDir($includeDir);
    push (@includeDirs, $relativeIncludeDir);
    
    my $srcDir = $module->getAndroidCSourceFolder();
    if (-d $srcDir){
        addSrcFiles(\@srcDirs, $srcDir);
    }
    $srcDir = $module->getSharedCSourceFolder();
    if (-d $srcDir){
        addSrcFiles(\@srcDirs, $srcDir);
    }
}

for (my $i = 0; $i < @srcDirs; $i++){
    $srcDirs[$i] = getPathRelativeToRootDir($srcDirs[$i]);
}

push @includeDirs, "dependencies/expat-2.2.1/lib", "dependencies/SFMT-src-1.5.1";

push @srcDirs, "dependencies/SFMT-src-1.5.1/SFMT.c";

my @expatFiles = ("xmlparse.c", "xmlrole.c", "xmltok_ns.c", "xmltok.c");

for my $expatFile (@expatFiles){
    push @srcDirs, "dependencies/expat-2.2.1/lib/" . $expatFile;
}

my $cmakeFile = getAbsolutePathToRootDir() . '/CMakeLists.txt';

$, = " ";

open(my $fh, '>', $cmakeFile) or die "Could not open file $cmakeFile. Reason: $!";
print $fh "\n";
print $fh "# THIS FILE HAS BEEN AUTOMATICALLY GENERATED. DO NOT EDIT IT DIRECTLY!\n";
print $fh "\n";
print $fh "cmake_minimum_required(VERSION 3.4.1)\n";
print $fh "\n";
print $fh "add_definitions(-std=c99)\n";
print $fh "add_definitions(-DLTC_MINIMAL -DLTC_MRSA -DLTC_SOURCE -DLTM_DESC -DHAVE_MEMMOVE)\n";
print $fh "\n";
print $fh "include_directories(@includeDirs)\n";
print $fh "\n";
print $fh "add_library(ImpsEngine SHARED @srcDirs)\n";
print $fh "\n";
print $fh "target_link_libraries(ImpsEngine android log GLESv2 EGL)\n";
close $fh;


