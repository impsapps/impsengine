#!/usr/bin/perl

package BuildAndroidModule;

use strict;
use warnings;

BEGIN {push @INC, '.'}

use BuildModuleHelper;

my @modulesToBuild = getAllModulesToBuildInAValidOrderForModuleNames(@ARGV);

foreach my $moduleToBuild (@modulesToBuild){
    buildModuleForAndroid($moduleToBuild);
    buildModuleForIOS($moduleToBuild);
    buildModuleForWindows($moduleToBuild);
}
