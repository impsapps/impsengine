#!/usr/bin/perl

package BuildModuleHelper;

use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getAbsolutePathToRootDir getPathRelativeToRootDir getModuleWithName getHashMapReferenceToAllModules getAllModulesToBuildInAValidOrderForModuleNames buildModuleForIOS buildModuleForAndroid buildModuleForWindows);


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
                "c" => ["shared"]
            },
            "#random-number-generator-sfmt" => {
                "c" => [],
                "symlink-headers" => "false"
            }
        },
        
        "common" => {
            "#androidlib" => {
                "c" => []
            },
            "#clib" => {
                "c" => ["android", "shared"]
            },
            "#concurrentlib" => {
                "c" => ["shared"]
            },
            "#expat" => {
                "c" => [],
                "symlink-headers" => "false"
            },
            "#input-output" => {
                "c" => ["shared"]
            },
            "#mathlib" => {
                "c" => ["shared"]
            },
            "#multi-touch" => {
                "c" => ["shared"],
                "include" => ["opengl", "clib"]
            },
            "#opengl" => {
                "c" => ["shared"],
                "include" => ["clib"]
            },
            "#opengl-renderer" => {
                "c" => ["android", "shared"],
                "include" => ["clib", "multi-touch"]
            }
        },
        
        "utilities" => {
            "#date" => {
                "c" => ["shared"]
            },
            "#url" => {
                "c" => ["shared"]
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

sub getHashMapReferenceToAllModules{
    return $modules;
}

sub privateAddModulesToBuildToArray{
    my $module = shift;
    my $modulesArrayRef = shift;
    my $isAlreadyInModulesArray = 0;

    foreach my $moduleInArray (@$modulesArrayRef){
        if($module->getName() eq $moduleInArray->getName()){
            $isAlreadyInModulesArray = 1;
            last;
        }
    }

    if($isAlreadyInModulesArray == 0){
        my @includedModuleNames = $module->getIncludes();
        foreach my $includedModuleName(@includedModuleNames){
            my $includedModule = getModuleWithName($includedModuleName);
            if(not $includedModule){
                die "Error in BuildModuleHelper.pl: Module with name \"$includedModuleName\" not found!";
            }
            privateAddModulesToBuildToArray($includedModule, $modulesArrayRef);
        }
        push(@$modulesArrayRef, $module);
    }
}

sub getAllModulesToBuildInAValidOrderForModuleNames{
    my @moduleNames = @_;
    my @modulesToBuild = ();

    foreach my $moduleName (@moduleNames){
		if($moduleName eq "all"){
			foreach my $module (values %$modules){
				privateAddModulesToBuildToArray($module, \@modulesToBuild);
			}
		}else{
			my $module = getModuleWithName($moduleName);
			if(not $module){
            die "Error: module with name \"$moduleName\" not found!";
			}
			privateAddModulesToBuildToArray($module, \@modulesToBuild);
		}
    }

    return @modulesToBuild;
}

sub privateExecuteGenerateGenerics{
    my @arguments = @_;
    chdir "../generate-generics";
    system("perl GenerateGenericsMain.pl @arguments") == 0 or die "Error in generate-generics: $?";
    chdir $cwd;
}

sub privateBuildModuleSharedIfNeeded{
    my $module = shift;
    if($module->shouldBuildSharedCSourceFolder()){
        my @args = ($module->getModuleGroup(), $module->getName(), $module->getSharedCSourceFolder());
        foreach my $includeName ($module->getIncludes()){
            my $includedModule = getModuleWithName($includeName);
            if (not $includedModule){
                die "Module \"$includeName\" cannot be included in module \"" . $module->getName() . "\". It is not existing.";
            }
            push @args, $includedModule->getSharedCSourceFolder();
        }
        privateExecuteGenerateGenerics(@args);
    }
}

sub buildModuleForAndroid{
    my $module = shift;
    privateBuildModuleSharedIfNeeded($module);
    
    if($module->shouldBuildAndroidCSourceFolder()){
        my @args = ($module->getModuleGroup(), $module->getName() . "-android", $module->getAndroidCSourceFolder());
        if ($module->shouldBuildSharedCSourceFolder()){
            push @args, $module->getSharedCSourceFolder();
        }
        foreach my $includeName ($module->getIncludes()){
            my $includedModule = getModuleWithName($includeName);
            if (not $includedModule){
                die "Module \"$includeName\" cannot be included in module \"" . $module->getName() . "\". It is not existing.";
            }
            
            if($module->shouldBuildAndroidCSourceFolder()){
                push @args, $includedModule->getAndroidCSourceFolder();
            }
            if ($module->shouldBuildSharedCSourceFolder()){
                push @args, $includedModule->getSharedCSourceFolder();
            }
        }
        privateExecuteGenerateGenerics(@args);
    }
	
	$module->symlinkAndroidHeadersForModuleIfNeeded();
}

sub buildModuleForIOS{
    my $module = shift;
    privateBuildModuleSharedIfNeeded($module);
    
    if($module->shouldBuildIOSCSourceFolder()){
        my @args = ($module->getModuleGroup(), $module->getName() . "-ios", $module->getIOSCSourceFolder());
        if ($module->shouldBuildSharedCSourceFolder()){
            push @args, $module->getSharedCSourceFolder();
        }
        if($module->hasIncludes()){
            foreach my $includeName ($module->getIncludes()){
                my $includedModule = getModuleWithName($includeName);
                if (not $includedModule){
                    die "Module \"$includeName\" cannot be included in module \"" . $module->getName() . "\". It is not existing.";
                }
                
                if($module->shouldBuildIOSCSourceFolder()){
                    push @args, $includedModule->getIOSCSourceFolder();
                }
                if ($module->shouldBuildSharedCSourceFolder()){
                    push @args, $includedModule->getSharedCSourceFolder();
                }
            }
        }
        privateExecuteGenerateGenerics(@args);
    }
    
    $module->symlinkIOSHeadersForModuleIfNeeded();
}

sub buildModuleForWindows{
	my $module = shift;
    privateBuildModuleSharedIfNeeded($module);
    
    $module->symlinkWindowsHeadersForModuleIfNeeded();
}

1;
