#!/usr/bin/perl

package BuildIOSModule;

use strict;
use warnings;

BEGIN {push @INC, '.'}

use BuildModuleHelper;

my @modulesToBuild = getAllModulesToBuildInAValidOrderForModuleNames(@ARGV);

foreach my $moduleToBuild (@modulesToBuild){
    buildModuleForIOS($moduleToBuild);
}
