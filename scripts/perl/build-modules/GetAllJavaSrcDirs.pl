#!/usr/bin/perl

package BuildAndroidModule;

use strict;
use warnings;

BEGIN {push @INC, '.'}

use Cwd;
use BuildModuleHelper;
use Module;

my @modulesToBuild = getAllModulesToBuildInAValidOrderForModuleNames(@ARGV);
my @srcDirs = ();

foreach my $module (@modulesToBuild){
    my $srcDir = $module->getJavaSourceFolder();
    if(-d $srcDir){
        push (@srcDirs, $srcDir);
    }
}

$, = " ";
print @srcDirs;
