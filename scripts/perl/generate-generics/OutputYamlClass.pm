#!/usr/bin/perl

use strict;
use warnings;

package OutputYamlClass;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(printFromYamlToFile);

use Constants;
use Expressions;
use Helper;
use OutputYamlClassHelper;
use OutputYamlClassParser;

sub printFromYamlToFile{
  my $class = shift;
  my $classProvider = shift;
  my $outputDir = shift;

  die "Cannot printFromYamlToFile with not an yaml class \"" . $class->getClassName() . "\"." if (not $class->{yaml});

  my $className = $class->getClassName();
  my $yaml = $class->{yaml};

  return if (exists $yaml->{__template__});

  my $parser = OutputYamlClassParser->new($classProvider, $class->{filePath});

  my $classnameToGenerate = $class->{yaml}->{__generate__};
  my @initLines = ();
  my @deinitLines = ();
  my $result = $parser->parseObject($classnameToGenerate, $yaml, \@initLines, \@deinitLines);

  my $attributesName = ${className} . "Attributes";
  my $referencesStructName = ${className} . "Ref";

  my $fileName = $outputDir . "/" . $className . ".h";
  open(my $fh, ">", $fileName) or die "Could not open file \"$fileName\".";

  print $fh $copyright;

  print $fh "\n";
  print $fh "\n";
  print $fh "#ifndef ${className}_h\n";
  print $fh "#define ${className}_h\n";
  print $fh "\n";
  print $fh "#include \"IALibrary.h\"\n";
  foreach my $include (sort keys %{$parser->{includes}}){
    print $fh "#include \"$include.h\"\n";
  }
  print $fh "\n";
  print $fh "typedef struct{\n";
  foreach my $objectAttribute (@{$parser->{objectAttributes}}){
    print $fh "\t" . $objectAttribute . "\n";
  }
  print $fh "} $attributesName;\n";
  print $fh "\n";
  print $fh "typedef struct{\n";
  foreach my $objectReference (@{$parser->{objectReferences}}){
    print $fh "\t" . $objectReference . "\n";
  }
  print $fh "} $referencesStructName;\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "static $classnameToGenerate * ${className}_new${classnameToGenerate}FromYaml(const $attributesName * attr, $referencesStructName * refsOut) {\n";
  foreach my $initLine (@initLines){
    print $fh $initLine;
  }
  print $fh "\treturn $result;\n"; #don't use deinit lines to destroy result
  print $fh "}\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "#endif\n";
  print $fh "\n";
  close($fh);
}

sub parseYaml{
  my $yaml = shift;
  my $fh = shift;
  my $context = shift;
  my $contextParams = @_;

#  if (ref $newYaml eq 'HASH'){
    #dict
  #  }elsif (ref $newYaml eq 'ARRAY'){
    #array
  #}elsif ($newYaml and not ref $newYaml){
    #scalar
  #}
}

1;
