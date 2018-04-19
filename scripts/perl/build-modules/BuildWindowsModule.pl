#!/usr/bin/perl

package BuildWindowsModule;

use strict;
use warnings;

BEGIN {push @INC, '.'}

use BuildModuleHelper;

my @modulesToBuild = getAllModulesToBuildInAValidOrderForModuleNames(@ARGV);

foreach my $moduleToBuild (@modulesToBuild){
    buildModuleForWindows($moduleToBuild);
}

