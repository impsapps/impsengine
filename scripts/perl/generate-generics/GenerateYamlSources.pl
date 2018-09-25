#!/usr/bin/perl

use strict;
use warnings;

BEGIN {push @INC, '.'}

$, = " ";
print "Build Args: " . "@ARGV" . "\n";

my $usage =
  "Usage: perl GenerateGenericsMain.pl [option, ...]\n" .
    "\"option\" must be one of the following:\n" .
    "-Y{yamlSourceFile} ... a yaml source file\n" .
    "-D{genDir} ... the dir where to save generated files [required]\n" .
    "-I{additionalIncludeDir} ... an include dir [optional]\n" .
    "-R{resourceProviderDir} ... Additionally to the behavior of an additional include dir, a resource provider dir will be searched for resource providers [optional]\n" .
    "Directories will not be searched recursively.\n";

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
use ParsingYaml;
use Constants;
use OutputYamlClass;

my $genDir = "";
my @sourceYamlFiles = ();
my @additionalIncludeDirs = ();
my @resourceProviderDirs = ();

foreach my $arg (@ARGV){
  if ($arg =~ m/-(\w)(.+)/){
    my $option = $1;
    my $value = $2;
    if ($option eq "D") {
      $value =~ s/\\/\//g;
      $genDir = $value;
    } elsif ($option eq "Y") {
      $value =~ s/\\/\//g;
      push @sourceYamlFiles, $value;
    } elsif ($option eq "I") {
      $value =~ s/\\/\//g;
      push @additionalIncludeDirs, $value;
    } elsif ($option eq "R") {
      $value =~ s/\\/\//g;
      push @resourceProviderDirs, $value;
    }
  }else{
    die "Invalid arg: \"$arg\".\n" . $usage;
  }
}

die "No gen dir specified.\n" . $usage if ($genDir eq "");
die "No sources specified.\n" . $usage if (scalar @sourceYamlFiles == 0);

foreach my $sourceYamlFile (@sourceYamlFiles){
  if (not -f $sourceYamlFile) {
    die "Yaml source file \"$sourceYamlFile\" is not a valid file.";
  }
}

my $classProvider = ClassProvider->new();

foreach my $additionalIncludeDir (@additionalIncludeDirs){
  next if ($additionalIncludeDir eq $genDir);
  $classProvider->addFileDir($additionalIncludeDir);
}

my %resourceProviders = ();
foreach my $resourceProviderDir (@resourceProviderDirs){
  my @headerFiles = getHeaderFilesForDir($resourceProviderDir);

}

my @sourceYamlClassNames = ();
foreach my $sourceYamlFile (@sourceYamlFiles){
  my $className = getClassNameForYamlFile($sourceYamlFile);
  $classProvider->addYamlFile($sourceYamlFile);
  push @sourceYamlClassNames, $className;
}

foreach my $yamlClass (@sourceYamlClassNames){
  my $class = $classProvider->getClass($yamlClass);
  if (defined $class){
    printFromYamlToFile($class, $classProvider, $genDir);
  }
}
