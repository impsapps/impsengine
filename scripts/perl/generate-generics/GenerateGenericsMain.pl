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
use Constants;
use OutputHeaderFile;

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
      $value =~ s/\\/\//g;
      $genDir = $value;
    } elsif ($option eq "S") {
      $value =~ s/\\/\//g;
      push @sourceDirs, $value;
    } elsif ($option eq "I") {
      $value =~ s/\\/\//g;
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


my $classProvider = ClassProvider->new();

my @sourceHeaderFiles = ();
my @sourceClassNames = ();
foreach my $sourceDir (@sourceDirs){
  next if ($sourceDir eq $genDir);
  push @sourceHeaderFiles, getHeaderFilesForDir($sourceDir);
  $classProvider->addFileDir($sourceDir);
}

foreach my $sourceHeaderFile (@sourceHeaderFiles){
  my $className = getClassNameWithExtensionForHeaderFile($sourceHeaderFile);
  push @sourceClassNames, $className;
}

foreach my $additionalIncludeDir (@additionalIncludeDirs){
  next if ($additionalIncludeDir eq $genDir);
  $classProvider->addFileDir($additionalIncludeDir);
}

if (not -d $genDir) {
  make_path $genDir or die "Cannot create dir \"$genDir\".";
}

my @doxygenClassNames = ();
my @doxygenHeaderFiles = ();
foreach my $className (sort @sourceClassNames){
  my $class = $classProvider->getClass($className);
  if (defined $class) {
    printHeaderFilesForClass($class, $classProvider, $genDir);
    if($class->isValidClass()){
      push @doxygenClassNames, $className;
      if ($class->isEvent()) {
        my $eventClassName = getEventNameForClassName($className);
        push @doxygenClassNames, $eventClassName;
        push @doxygenHeaderFiles, $genDir . "/$eventClassName.h";
      }
    }
  }
}

my $moduleGenericsPath = $genDir . "/" . $moduleName . $genericsModuleExtension;
open HEADER, ">", $moduleGenericsPath or die "unable to open header file $moduleGenericsPath for writing!";

if ($moduleGroup ne "") {
  print HEADER "/**\n";
  print HEADER " * \\addtogroup $moduleGroup\n";
  print HEADER " */\n\n";
}

print HEADER "/**\n";
print HEADER " * \\addtogroup $moduleName\n";
if ($moduleGroup ne "") {
  print HEADER " * \\ingroup $moduleGroup\n";
}
print HEADER " * \@{\n";
print HEADER " */\n";


foreach my $className (sort @doxygenClassNames){
  print HEADER "/// \\class $className\n";
}

push @doxygenHeaderFiles, @sourceHeaderFiles;
@doxygenHeaderFiles = map {$_ =~ s/.*\///; $_} @doxygenHeaderFiles;
foreach my $doxygenHeaderFile (sort @doxygenHeaderFiles){
  print HEADER "/// \\file $doxygenHeaderFile\n";
}

print HEADER "/**\n";
print HEADER " * \@}\n";
print HEADER " */\n\n";
close HEADER;
