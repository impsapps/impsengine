#!/usr/bin/perl

package BuildModuleHelper;

use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getAbsolutePathToRootDir getPathRelativeToRootDir getModuleWithName getAllModuleGroupNamesInValidOrder getAllModuleNamesForGroupNameInValidOrder);


use Cwd;
use Module;
use File::Spec;

my $cwd = getcwd();

my $pathToRootDir = "../../..";

chdir $pathToRootDir;
my $absolutePathToRootDir = getcwd();
chdir $cwd;

my $engineStructure = {
  "modules" => {
    "advanced-math" => {
      "#random-number-generator" => {
        "c" => ["shared"],
        "dep" => ["clib", "sfmt"]
      },
      "#sfmt" => {
        "external-include-dirs" => ["dependencies/SFMT-src-1.5.1"],
        "external-src-files" => ["dependencies/SFMT-src-1.5.1/SFMT.c"],
        "no-generics" => 1
      }
    },

    "common" => {
      "#androidlib" => {
        "c" => ["android"],
        "dep" => ["clib"]
      },
      "#clib" => {
        "c" => ["android", "ios", "shared", "windows"]
      },
      "#concurrentlib" => {
        "c" => ["android", "shared"],
        "dep" => ["clib"]
      },
      "#expat" => {
        "external-include-dirs" => ["dependencies/expat-2.2.1/lib"],
        "external-src-files" => [
        "dependencies/expat-2.2.1/lib/xmlparse.c",
        "dependencies/expat-2.2.1/lib/xmlrole.c",
        "dependencies/expat-2.2.1/lib/xmltok_ns.c",
        "dependencies/expat-2.2.1/lib/xmltok.c"
        ],
        "no-generics" => 1
      },
      "#input-output" => {
        "c" => ["android", "ios", "shared", "windows"],
        "dep" => ["clib", "expat"]
      },
      "#mathlib" => {
        "c" => ["shared"]
      },
      "#multi-touch" => {
        "c" => ["android", "shared"],
        "dep" => ["opengl", "clib"]
      },
      "#opengl" => {
        "c" => ["android", "ios", "shared", "windows"],
        "dep" => ["clib", "expat", "input-output", "mathlib"]
      },
      "#opengl-renderer" => {
        "c" => ["android", "ios", "shared"],
        "dep" => ["clib", "multi-touch", "opengl"]
      }
    },

    "misc" => {
      "#bundle-info" => {
        "c" => ["android", "ios", "shared"],
        "dep" => ["clib"]
      }
    },

    "utilities" => {
      "#date" => {
        "c" => ["android", "ios", "shared"],
        "dep" => ["clib"]
      },
      "#url" => {
        "c" => ["android", "ios", "shared"],
        "dep" => ["opengl"]
      }
    }
  }
};


setupModuleWithAbsolutePathToRootDirAndCWD($absolutePathToRootDir, $cwd);

my $modules = {};

sub setupModulesRecursively{
  my $structure = shift;
  my $pathToStructure = shift;

  foreach my $structureElementKey (keys %$structure){
    my $structureElement = $structure->{$structureElementKey};
    if($structureElementKey =~ m/^\#(.*)/){
      my $name = $1;
      $modules->{$name} = new Module($name, $structureElement, $pathToStructure);
    }else{
      my $pathToStructureElement;
      if($pathToStructure =~ m/[^\/]$/){
        $pathToStructureElement = $pathToStructure . "/" . $structureElementKey;
      }else{
        $pathToStructureElement = $pathToStructure . $structureElementKey;
      }
      setupModulesRecursively($structureElement, $pathToStructureElement);
    }
  }
}

setupModulesRecursively($engineStructure, "");

sub getAbsolutePathToRootDir{
  return $absolutePathToRootDir;
}

sub getPathRelativeToRootDir{
  my $absPath = shift;
  my $relPath = File::Spec->abs2rel( $absPath, $absolutePathToRootDir );
  return $relPath;
}

sub getModuleWithName{
  my $moduleName = shift;
  return $modules->{$moduleName};
}

sub getAllModuleGroupNamesInValidOrder{
  return ("common", "advanced-math", "utilities", "misc");
}

sub getAllModuleNamesForGroupNameInValidOrder{
  my $groupName = shift;
  if ($groupName eq "common") {
    return ("clib", "mathlib", "androidlib", "concurrentlib", "expat", "input-output", "opengl", "multi-touch", "opengl-renderer");
  } elsif ($groupName eq "advanced-math") {
    return ("sfmt", "random-number-generator");
  }elsif ($groupName eq "utilities") {
    return ("date", "url");
  } elsif ($groupName eq "misc") {
    return ("bundle-info");
  } else {
    return ();
  }
}

sub privateExecuteGenerateGenerics{
  my @arguments = @_;
  chdir "../generate-generics";
  system("perl GenerateGenericsMain.pl @arguments") == 0 or die "Error in generate-generics: $?";
  chdir $cwd;
}

1;
