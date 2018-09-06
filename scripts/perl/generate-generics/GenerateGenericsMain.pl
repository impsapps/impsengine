#!/usr/bin/perl

use strict;
use warnings;

BEGIN {push @INC, '.'}

my $usage =
"Usage: perl GenerateGenericsMain.pl [option, ...]\n" .
"\"option\" must be one of the following:\n" .
"-N{moduleName} ... the name of the module [required]\n" .
"-D{genDir} ... the dir where to save generated files [required]\n" .
"-S{sourceDir} ... a source dir [at least one required]\n" .
"-I{additionalIncludeDir} ... an include dir [optional]\n" .
"-G{groupName} ... the group name of the module [optional]\n" .
"Directories will not be searched recursively.\n";


my $genericsModuleExtension = "_moduledesc_generated.h";


package Main;

BEGIN {
  use Cwd 'abs_path';
  my $absPath = abs_path($0);
  $absPath =~ s/\/[^\/]*$//;
  push @INC, $absPath;
}

use File::Path qw(make_path);

use Class;
use ClassProvider;
use Attribute;
use Function;
use ParsingHeader;
use ParsingYaml;
use Constants;
use OutputHeaderFile;
use OutputYamlClass;

my $moduleName = "";
my $genDir = "";
my @sourceDirs = ();
my @additionalIncludeDirs = ();
my $moduleGroup = "";

foreach my $arg (@ARGV){
  if ($arg =~ m/-(\w)(.+)/){
    my $option = $1;
    my $value = $2;
    if ($option eq "N") {
      $moduleName = $value;
    } elsif ($option eq "D") {
      $genDir = $value;
    } elsif ($option eq "S") {
      push @sourceDirs, $value;
    } elsif ($option eq "I") {
      push @additionalIncludeDirs, $value;
    } elsif ($option eq "G") {
      $moduleGroup = $value;
    }
  }else{
    die "Invalid arg: \"$arg\".\n" . $usage;
  }
}

die "No module name specified.\n" . $usage if ($moduleName eq "");
die "No gen dir specified.\n" . $usage if ($genDir eq "");
die "No source dir specified.\n" . $usage if (scalar @sourceDirs == 0);


my $classProvider = new ClassProvider();

my @sourceHeaderFiles = ();
my @sourceYamlFiles = ();
my @sourceClassNames = ();
my @sourceYamlClassNames = ();
foreach my $sourceDir (@sourceDirs){
  next if ($sourceDir eq $genDir);
  push @sourceHeaderFiles, getHeaderFilesForDir($sourceDir);
  push @sourceYamlFiles, getYamlFilesForDir($sourceDir);
  $classProvider->addFileDir($sourceDir);
}

foreach my $sourceHeaderFile (@sourceHeaderFiles){
  my $className = getClassNameWithExtensionForHeaderFile($sourceHeaderFile);
  push @sourceClassNames, $className;
}

foreach my $sourceYamlFile (@sourceYamlFiles){
  my $className = getClassNameForYamlFile($sourceYamlFile);
  push @sourceClassNames, $className;
  push @sourceYamlClassNames, $className;
}

foreach my $additionalIncludeDir (@additionalIncludeDirs){
  next if ($additionalIncludeDir eq $genDir);
  $classProvider->addFileDir($additionalIncludeDir);
}

if (not -d $genDir) {
  make_path $genDir or die "Cannot create dir \"$genDir\".";
}

foreach my $className (sort @sourceClassNames){
  my $class = $classProvider->getClass($className);
  if (defined $class) {
    printHeaderFilesForClass($class, $classProvider, $genDir);
  }
}

foreach my $className (sort @sourceYamlClassNames){
  my $class = $classProvider->getClass($className);
  if (defined $class) {
    printFromYamlToFile($class, $classProvider, $genDir);
  }
}

my $moduleGenericsPath = $genDir . "/" . $moduleName . $genericsModuleExtension;
open HEADER, ">", $moduleGenericsPath or die "unable to open header file $moduleGenericsPath for writing!";

print HEADER "/**\n";
print HEADER " * \\addtogroup $moduleGroup\n";
print HEADER " */\n\n";


print HEADER "/**\n";
print HEADER " * \\addtogroup $moduleName\n";
print HEADER " * \\ingroup $moduleGroup\n";
print HEADER " * \@{\n";
print HEADER " */\n";

foreach my $className (sort @sourceClassNames){
  my $class = $classProvider->getClass($className);
  if($class && $class->isValidClass()){
    print HEADER "/// \\class $className\n";
  }
}

foreach my $headerFile (@sourceHeaderFiles){
  print HEADER "/// \\file $headerFile\n";
}

print HEADER "/**\n";
print HEADER " * \@}\n";
print HEADER " */\n\n";
close HEADER;
