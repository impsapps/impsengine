#!/usr/bin/perl

package CreateCMakeLists;

use strict;
use warnings;

BEGIN {push @INC, 'scripts/perl/build-modules'}

our $pathToRootDir = ".";

use Cwd;
use List::MoreUtils qw{ any };
use BuildModuleHelper;
use Module;
use Constants;

BuildModuleHelper::initialize(".");


sub addSrcHeaderAndCFiles {
  my $srcHeaderFiles = shift;
  my $srcCFiles = shift;
  my $filePath = shift;

  opendir(my $dh, $filePath) or die "Could not open $filePath. Reason: $!";
  my @names = readdir($dh);
  closedir($dh);

  foreach my $name (@names){
    my $newName = $filePath . '/' . $name;
    if(-f $newName){
      if ($newName =~ m/\.(h)$/){
        push @{$srcHeaderFiles}, $newName;
      }
      if ($newName =~ m/\.(c|m)$/){
        push @{$srcCFiles}, $newName;
      }
    }elsif(-d $newName and not $name =~ m/^\./){
      addSrcHeaderAndCFiles($srcHeaderFiles, $srcCFiles, $newName);
    }
  }
}

sub getAllSrcHeaderAndCFilesRelative {
  my @srcDirs = @_;
  my @srcHeaderFiles = ();
  my @srcCFiles = ();
  foreach my $srcDir (@srcDirs){
    if (-d $srcDir){
        addSrcHeaderAndCFiles(\@srcHeaderFiles, \@srcCFiles, $srcDir);
    }
  }
  for (my $i = 0; $i < @srcHeaderFiles; $i++){
      $srcHeaderFiles[$i] = getPathRelativeToRootDir($srcHeaderFiles[$i]);
  }
  for (my $i = 0; $i < @srcCFiles; $i++){
      $srcCFiles[$i] = getPathRelativeToRootDir($srcCFiles[$i]);
  }
  @srcHeaderFiles = sort @srcHeaderFiles;
  @srcCFiles = sort @srcCFiles;
  return \@srcHeaderFiles, \@srcCFiles;
}

sub getAllDirs {
  my $dirs = shift;
  my $filePath = shift;

  opendir(my $dh, $filePath) or die "Could not open $filePath. Reason: $!";
  my @names = readdir($dh);
  closedir($dh);

  push @{$dirs}, $filePath;
  foreach my $name (@names){
    my $newName = $filePath . '/' . $name;
    if(-d $newName and not $name =~ m/^\./){
      getAllDirs($dirs, $newName);
    }
  }
}

sub getAllIncludeDirsRelative {
  my @srcDirs = @_;
  my @includeDirs = ();
  foreach my $srcDir (@srcDirs){
    if (-d $srcDir){
      getAllDirs(\@includeDirs, $srcDir);
    }
  }
  for (my $i = 0; $i < @includeDirs; $i++){
    $includeDirs[$i] = getPathRelativeToRootDir($includeDirs[$i]);
  }
  @includeDirs = sort @includeDirs;
  return @includeDirs;
}

sub getLibName{
  my $moduleName = shift;
  my $libName = "ia" . $moduleName;
  $libName =~ s/-/_/;
  return $libName;
}

my $cmakeFile = getAbsolutePathToRootDir() . '/CMakeLists.txt';

$, = " ";

open(my $fh, '>', $cmakeFile) or die "Could not open file $cmakeFile. Reason: $!";
print $fh "\n";
print $fh "# THIS FILE HAS BEEN AUTOMATICALLY GENERATED. DO NOT EDIT IT DIRECTLY!\n";
print $fh "\n";
print $fh "cmake_minimum_required(VERSION 3.12.1)\n";
print $fh "include_guard()\n";
print $fh "\n";
print $fh "if(NOT DEFINED IA_PLATFORM)\n";
print $fh "\tmessage(FATAL_ERROR \"IA_PLATFORM is not set. It must be one of \\\"android\\\", \\\"ios\\\" or \\\"windows\\\".\")\n";
print $fh "endif()\n";
print $fh "\n";
print $fh "set(CMAKE_C_FLAGS_DEBUG \"\${CMAKE_C_FLAGS_DEBUG} -DDEBUG -UNDEBUG\")\n";
print $fh "set(CMAKE_CXX_FLAGS_DEBUG \"\${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -UNDEBUG\")\n";
print $fh "set(CMAKE_C_FLAGS_RELEASE \"\${CMAKE_C_FLAGS_RELEASE} -UDEBUG -DNDEBUG\")\n";
print $fh "set(CMAKE_CXX_FLAGS_RELEASE \"\${CMAKE_CXX_FLAGS_RELEASE} -UDEBUG -DNDEBUG\")\n";
print $fh "list(APPEND CMAKE_MODULE_PATH \${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)\n";
print $fh "\n";
print $fh "add_definitions(-DHAVE_MEMMOVE)\n";
print $fh "find_package(HelperFunctions)\n";
print $fh "\n";
print $fh "\n";

my $cwd = getcwd();

my @groupNames = getAllModuleGroupNamesInValidOrder();
foreach my $groupName (@groupNames){
  print $fh "# --------------  Modules for group \"$groupName\"  --------------n";
  print $fh "\n";
  print $fh "\n";
  my @moduleNames = getAllModuleNamesForGroupNameInValidOrder($groupName);
  foreach my $moduleName (@moduleNames){
    my $module = getModuleWithName($moduleName);
    my $libName = getLibName($moduleName);

    print $fh "unset(ia_include_dirs)\n";
    print $fh "unset(ia_source_h_files)\n";
    print $fh "unset(ia_source_c_files)\n";

    if ($module->hasCSourceFolders($sharedSourceFolder)) {
      my @includeDirs = getAllIncludeDirsRelative($module->getCSourceFolders($sharedSourceFolder));
      (my $srcHeaderFiles, my $srcCFiles) = getAllSrcHeaderAndCFilesRelative($module->getCSourceFolders($sharedSourceFolder));
      if (@includeDirs > 0) {
        print $fh "list(APPEND ia_include_dirs @includeDirs)\n";
        print $fh "list(APPEND ${libName}_doxygen_source_dirs \${ia_include_dirs})\n";
      }
      if (@$srcHeaderFiles > 0) {
        print $fh "list(APPEND ia_source_h_files @$srcHeaderFiles)\n";
      }
      if (@$srcCFiles > 0) {
        print $fh "list(APPEND ia_source_c_files @$srcCFiles)\n";
      }
    }

    foreach my $folderName (@possibleSourceFolderNames){
      if ($module->hasCSourceFolders($folderName)) {
        my @includeDirs = getAllIncludeDirsRelative($module->getCSourceFolders($folderName));
        (my $srcHeaderFiles, my $srcCFiles) = getAllSrcHeaderAndCFilesRelative($module->getCSourceFolders($folderName));
        if (@includeDirs == 0 && @$srcHeaderFiles == 0 && @$srcCFiles == 0) {
          next;
        }
        print $fh "if(\${IA_PLATFORM} STREQUAL $folderName)\n";
        if (@includeDirs) {
          print $fh "\tlist(APPEND ia_include_dirs @includeDirs)\n";
        }
        if (@$srcHeaderFiles > 0) {
          print $fh "\tlist(APPEND ia_source_h_files @$srcHeaderFiles)\n";
        }
        if (@$srcCFiles > 0) {
          print $fh "\tlist(APPEND ia_source_c_files @$srcCFiles)\n";
        }
        print $fh "endif()\n";
      }
    }

    my $relativeCSourceFolder = $module->getCGroupPath();
    $relativeCSourceFolder =~ s/^$cwd\/?//;
    printf $fh "source_group(TREE \${CMAKE_CURRENT_SOURCE_DIR}/%s FILES \${ia_source_h_files} \${ia_source_c_files})\n", $relativeCSourceFolder;

    my @externalIncludeDirs = $module->getExternalIncludeDirs();
    if (@externalIncludeDirs) {
      print $fh "list(APPEND ia_include_dirs @externalIncludeDirs)\n";
    }
    my @externalSrcFiles = $module->getExternalSrcFiles();
    if (@externalSrcFiles) {
      print $fh "list(APPEND ia_source_c_files @externalSrcFiles)\n";
    }

    my $genDir = "include/\${IA_PLATFORM}/generated";
    print $fh "list(APPEND ia_include_dirs $genDir)\n";

    print $fh "\n";
    print $fh "if (ia_source_c_files)\n";
    print $fh "\tadd_library($libName STATIC \${ia_source_h_files} \${ia_source_c_files})\n";
    print $fh "\ttarget_include_directories($libName PUBLIC \${ia_include_dirs})\n";


    my @dependencies = $module->getDependencies();
		if (scalar @dependencies > 0){
			foreach my $i (0 .. $#dependencies){
				$dependencies[$i] = getLibName($dependencies[$i]);
			}
      print $fh "\ttarget_link_libraries($libName @dependencies)\n";
    }

		my @androidDependencies = $module->getDependencies("android");
		if (scalar @androidDependencies > 0){
			print $fh "\tif(\${IA_PLATFORM} STREQUAL android)\n";
			print $fh "\t\ttarget_link_libraries($libName @androidDependencies)\n";
			print $fh "\tendif()\n";
		}

		my @windowsDependencies = $module->getDependencies("windows");
		if (scalar @windowsDependencies > 0){
			print $fh "\tif(\${IA_PLATFORM} STREQUAL windows)\n";
			print $fh "\t\ttarget_link_libraries($libName @windowsDependencies)\n";
			print $fh "\tendif()\n";
		}

    if ($module->shouldGenerateGenerics()) {
      print $fh "\ttarget_generate_generics($libName $genDir)\n";
    }
    print $fh "\tinstall(FILES \${ia_source_h_files} DESTINATION \${CMAKE_CURRENT_SOURCE_DIR}/include/\${IA_PLATFORM})\n";

    print $fh "endif()\n";
    print $fh "\n";
    print $fh "\n";
    print $fh "\n";
  }
}

sub getModuleDescFile{
  my $moduleName = shift;
  return "\${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/${moduleName}_moduledesc_generated.h";
}

my @doxygenModuleNames = getAllDoxygenModuleNamesInValidOrder();
foreach my $doxygenModuleName (@doxygenModuleNames){
  print $fh "unset(ia_source_dirs)\n";
  print $fh "unset(ia_include_dirs)\n";
  print $fh "unset(ia_dep_files)\n";
  my $doxygenLibName = getLibName($doxygenModuleName);
  my $module = getModuleWithName($doxygenModuleName);
  my $groupName = $module->getGroup();
  my @deps = $module->getDependencies();
  foreach my $dep (@deps){
    if (any { $_ eq $dep} @doxygenModuleNames) {
      my $depLibName = getLibName($dep);
      print $fh "list(APPEND ia_dep_files " . getModuleDescFile($dep) . ")\n";
      print $fh "list(APPEND ia_include_dirs \${${depLibName}_doxygen_source_dirs})\n";
    }
  }
  print $fh "list(APPEND ia_source_dirs \${${doxygenLibName}_doxygen_source_dirs})\n";
  print $fh "list(TRANSFORM ia_source_dirs PREPEND \"-S\${CMAKE_CURRENT_SOURCE_DIR}/\")\n";
  print $fh "list(TRANSFORM ia_include_dirs PREPEND \"-I\${CMAKE_CURRENT_SOURCE_DIR}/\")\n";
  print $fh "add_custom_command(\n";
  print $fh "\tOUTPUT " . getModuleDescFile($doxygenModuleName) . "\n";
  print $fh "\tCOMMAND perl GenerateGenericsMain.pl \"-N${doxygenModuleName}\" \"-G${groupName}\" \"-D\${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated\" \${ia_source_dirs} \${ia_include_dirs}\n";
  print $fh "\tDEPENDS \${ia_dep_files}\n";
  print $fh "\tWORKING_DIRECTORY \${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics\n";
  print $fh ")\n";
}

print $fh "unset(ia_dep_files)\n";
foreach my $doxygenModuleName (@doxygenModuleNames){
  print $fh "list(APPEND ia_dep_files " . getModuleDescFile($doxygenModuleName) . ")\n";
}
print $fh "add_custom_target(\n";
print $fh "\tdoxygen_docs\n";
print $fh "\tCOMMAND doxygen doxygen.cmake.cfg\n";
print $fh "\tDEPENDS \${ia_dep_files}";
print $fh "\tWORKING_DIRECTORY \${CMAKE_CURRENT_SOURCE_DIR}/\n";
print $fh ")\n";
print $fh "\n";
close $fh;
