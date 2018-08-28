#!/usr/bin/perl

use strict;
use warnings;

BEGIN {
  push @INC, '.';
  push @INC, '../generate-generics';
}

my $usage =
"Usage: perl GenerateFromYamlMain.pl [option, ...]\n" .
"\"option\" must be one of the following:\n" .
"-D{genDir} ... the dir where to save generated files [required]\n" .
"-S{sourceDir} ... a source dir where yaml files are located [at least one required]\n" .
"-I{additionalIncludeDir} ... an include dir [optional]\n" .
"Directories will not be searched recursively.\n";

package Main;

use File::Path qw(make_path);

use Parsing;
use ClassProvider;

my $genDir = "";
my @sourceDirs = ();
my @additionalIncludeDirs = ();

foreach my $arg (@ARGV){
  if ($arg =~ m/-(\w)(.+)/){
    my $option = $1;
    my $value = $2;
    if ($option eq "D") {
      $genDir = $value;
    } elsif ($option eq "S") {
      push @sourceDirs, $value;
    } elsif ($option eq "I") {
      push @additionalIncludeDirs, $value;
    }
  }else{
    die "Invalid arg: \"$arg\".\n" . $usage;
  }
}

die "No gen dir specified.\n" . $usage if ($genDir eq "");
die "No source dir specified.\n" . $usage if (scalar @sourceDirs == 0);

if (not -d $genDir) {
  make_path $genDir or die "Cannot create dir \"$genDir\".";
}

my $classProvider = new ClassProvider();

foreach my $includeDir (@sourceDirs, @additionalIncludeDirs){
  next if ($includeDir eq $genDir);
  $classProvider->addHeaderFileDir($includeDir);
}

my @yamlFiles = ();
foreach my $sourceDir (@sourceDirs){
  next if ($sourceDir eq $genDir);
  push @yamlFiles, getYamlFilesForDir($sourceDir);
}

foreach my $yamlFile (@yamlFiles){
  my $className = getClassNameForYamlFile($yamlFile);
  open(my $fh, ">", $genDir . "/$className.h");
  print $fh "hello";
  close($fh);
}
