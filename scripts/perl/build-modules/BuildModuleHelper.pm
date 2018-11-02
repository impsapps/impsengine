#!/usr/bin/perl

package BuildModuleHelper;

use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getAbsolutePathToRootDir getPathRelativeToRootDir getModuleWithName getAllModuleGroupNamesInValidOrder getAllModuleNamesForGroupNameInValidOrder getAllDoxygenModuleNamesInValidOrder);


use Cwd;
use Module;
use File::Spec;


my $engineStructure = {
  "modules" => {
    "advanced-math" => {
      "#random-number-generator" => {
        "c" => ["shared"],
        "dep" => ["clib", "sfmt"]
      },
      "#sfmt" => {
        "external-include-dirs" => ["dependencies/sfmt"],
        "external-src-files" => ["dependencies/sfmt/SFMT.c"],
        "no-generics" => 1
      }
    },

    "common" => {
      "#androidlib" => {
        "c" => ["android"],
        "dep" => ["clib"]
      },
      "#clib" => {
        "c" => ["android", "ios", "shared", "windows"],
		    "android-dep" => ["android", "log"]
      },
      "#concurrentlib" => {
        "c" => ["android", "ios"],
        "dep" => ["clib"]
      },
      "#expat" => {
        "external-include-dirs" => ["dependencies/expat/expat/lib"],
        "external-src-files" => [
          "dependencies/expat/expat/lib/loadlibrary.c",
          "dependencies/expat/expat/lib/xmlparse.c",
          "dependencies/expat/expat/lib/xmlrole.c",
          "dependencies/expat/expat/lib/xmltok_ns.c",
          "dependencies/expat/expat/lib/xmltok.c"
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
        "c" => ["android", "shared", "windows"],
        "dep" => ["opengl", "clib"]
      },
      "#opengl" => {
        "c" => ["android", "ios", "shared", "windows"],
        "dep" => ["clib", "expat", "input-output", "mathlib"],
		    "android-dep" => ["GLESv2", "EGL"],
		    "windows-dep" => ["glew"]
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

my $modules = {};
my $absolutePathToRootDir = "";

sub initialize{
	my $pathToRootDir = shift or die "param \"\$pathToRootDir\" expected";

	my $cwd = getcwd();

	chdir $pathToRootDir;
	$absolutePathToRootDir = getcwd();
	chdir $cwd;

	setupModuleWithAbsolutePathToRootDirAndCWD($absolutePathToRootDir, $cwd);
	setupModulesRecursively($engineStructure, "");
}

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

sub getAbsolutePathToRootDir{
  return $absolutePathToRootDir;
}

sub getPathRelativeToRootDir{
  my $absPath = shift;
  my $relPath = File::Spec->abs2rel( $absPath, $absolutePathToRootDir );
  $relPath =~ s/\\/\//g;
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

sub getAllDoxygenModuleNamesInValidOrder{
  return ("clib", "mathlib", "input-output", "opengl", "multi-touch", "opengl-renderer", "bundle-info", "date", "url", "random-number-generator");
}

1;
