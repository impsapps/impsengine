#!/usr/bin/perl

my $usage =
"usage: ./CreateSymlinksForHeaders.pl [dirTo] [useSymlinks] [dirFrom, ...]\n" .
"dirTo ... dir where to put the symlinks in\n" .
"useSymlinks ... 0 for no, 1 for yes" .
"dirFrom ... dir where to take the header files from (recursively)\n";


package Main;

use File::Compare;
use File::Copy qw(copy);

use strict;
use warnings;

my $dirTo = $ARGV[0];
my $useSymlinks = $ARGV[1];

my @rootDirsFrom;

my $currentPosition = 2;
while ($currentPosition < scalar @ARGV){
    my $dirFrom = $ARGV[$currentPosition];
    if(-d $dirFrom){
        push(@rootDirsFrom, $dirFrom);
    }
    $currentPosition++;
}

if (@rootDirsFrom == 0){
    exit 0;
}

sub addHeaderFilesFromDirRecursively {
    my $dir = shift;
    my $headers = shift;
    
    opendir(DH, $dir) or die "Unable to open directory \"$dir\"!";
    my @names = readdir(DH);
    closedir(DH);
    
    foreach my $name (@names){
        next if substr ($name, 0, 1) eq '.';
        
        my $newName = $dir . '/' . $name;
        
        if(-f $newName){
            if($newName =~ m/\.h$/){
                our $header = {};
                $header->{"dir"} = $dir;
                $header->{"name"} = $name;
                push @$headers, $header;
            }
        }elsif(-d $newName){
            addHeaderFilesFromDirRecursively($newName, $headers);
        }
    }
    return 0;
}

sub hasDirOnlyHeaderFiles {
    my $dir = shift;
    
    opendir(DH, $dir) or die "Unable to open directory \"$dir\"!";
    my @names = readdir(DH);
    closedir(DH);
    
    my $hasOnlyHeaderFiles = 1;
    
    foreach my $name (@names){
        next if substr ($name, 0, 1) eq '.';
        
        my $newName = $dir . '/' . $name;
        
        if(-f $newName){
            if(not $newName =~ m/\.h$/){
                $hasOnlyHeaderFiles = 0;
            }
        }elsif(-d $newName){
            $hasOnlyHeaderFiles = 0;
        }
    }
    return $hasOnlyHeaderFiles;
}

if (hasDirOnlyHeaderFiles($dirTo) == 0){
    die "DirTo \"$dirTo\" has not only header files! Unsafe to clean dir! Please clear that dir manually!";
}

my @headers;
foreach my $rootDir (@rootDirsFrom){
    addHeaderFilesFromDirRecursively($rootDir, \@headers);
}

my %oldHeaders;

opendir(DH, $dirTo);
my @names = readdir(DH);
closedir(DH);

foreach my $name (@names){
    next if substr ($name, 0, 1) eq '.';
    
    my $newName = $dirTo . '/' . $name;
    
    if(-f $newName or -l $newName){
        $oldHeaders{$name} = $newName;
    }
}

foreach my $header (@headers){
    my $dir = $header->{"dir"};
    my $name = $header->{"name"};
    
    my $filePathTo = $dirTo . '/' . $name;
    my $filePathFrom = $dir . '/' . $name;
    
    if (exists $oldHeaders{$name}){
        unlink $oldHeaders{$name};
        delete $oldHeaders{$name};
    }
    
    if(not -f $filePathTo){
        if ($useSymlinks){
            my $symlink_exists = eval { symlink($filePathFrom,$filePathTo); 1 };
            $symlink_exists or die "symlink not available on platform which was requested!";
        }else{
            copy($filePathFrom, $filePathTo);
        }
    }else{
        if(compare($filePathTo, $filePathFrom) != 0){
            die "Detected distinct headers with same name! One already exported in \"$filePathTo\" and the other in \"$filePathFrom\".";
        }
    }
}

foreach my $oldHeader(values %oldHeaders){
    unlink $oldHeader or die "Couldn't unlink($oldHeader): $!";;
}



