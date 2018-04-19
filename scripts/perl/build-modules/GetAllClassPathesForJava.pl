#!/usr/bin/perl

package BuildAndroidModule;

use strict;
use warnings;

BEGIN {push @INC, '.'}

use Cwd;
use BuildModuleHelper;
use Module;

if(not exists($ARGV[0])){
    print "GetAllClassPathesForJava: illegal options\n";
    print "usage: ./GetAllClassPathesForJava.pl classPathSeperator\n";
    exit 0;
}

my $modules = getHashMapReferenceToAllModules();
my @srcDirs = ();

foreach my $module (values %$modules){
    my $srcDir = $module->getJavaSourceFolder();
    push (@srcDirs, $srcDir);
}

$, = $ARGV[0];
print @srcDirs;
print "\n";
