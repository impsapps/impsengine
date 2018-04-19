#!/usr/bin/perl

package BuildAndroidModule;

use strict;
use warnings;

BEGIN {push @INC, '.'}

use BuildModuleHelper;
use Module;

my @modulesToBuild = getAllModulesToBuildInAValidOrderForModuleNames(@ARGV);
my @includeDirs = ();

foreach my $module (@modulesToBuild){
    my $androidIncludeFolder = $module->getAndroidIncludeFolder();
	push(@includeDirs, $androidIncludeFolder);
}

$, = " ";

print @includeDirs;

