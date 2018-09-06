#!/usr/bin/perl

use strict;
use warnings;

package OutputYamlClass;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(printFromYamlToFile);

use Constants;
use ParsingYaml;


sub printFromYamlToFile{
  my $class = shift;
  our $classProvider = shift;
  my $outputDir = shift;

  die "Cannot printFromYamlToFile with not an yaml class \"" . $class->{className} . "\"." if (not $class->{yaml});

  my $className = $class->getClassName();
  my $yaml = $class->{yaml};

  return if (exists $yaml->{__template__});

  our $isCorrespondingObjectNeeded = 0;
  our @attributeLines = ();

  our @initLines = ();
  our @deinitLines = ();

  our @objectAttributes = ();

  sub parseValue{
    my $yaml = shift;
  }

  sub parseString{
    my $yaml = shift;
  }

  sub parseBoolean{
    my $yaml = shift;
  }

  sub parseFunction{
    my $yaml = shift;
  }

  sub parseObject{
    my $yaml = shift;
    my $classNameExpected = shift;
    my $variableNameToUse = shift;
    my $class = $classProvider->getClass($classNameExpected);

    my @keys = ();
    foreach my $key (keys %{$yaml}){
      if (not $key =~ m/^__.*__$/) {
        push @keys, $key;
      }
    }

    my $expectedClass = $classProvider->getClass($classNameExpected);
    die "Expected an Object of class \"${classNameExpected}\", but it is not a valid object." if(not $expectedClass->isObject());

    my @initFunctions = $expectedClass->getValidInitFunctions();
    if (@initFunctions == 0) {
      @initFunctions = $expectedClass->getValidMakeFunctions();
    }
    foreach my $initFunction (@initFunctions){
      my $params = $function->{params};
      $params = removeFirstParamFromParams($params);
      $params = normalizeParams($params);
      while ($params =~ m/$matchSingleNormalizedParam/g) {
        my $param = $1;
        if ($param =~ m/$matchType\s*$matchName/) {
          # body...
        }else{
          if (not $param =~ m/$matchFunction/){
            die "Internal error. Invalid matched param \"$param\".";
          }

        }



      }


    }
  }

  sub parseObjectArray{
    my $yamlClass = shift;
    my $yaml = shift;
  }

  parseObject($yaml, $class->{yaml}->{__generate__}, "IA_result");

  open(my $fh, ">", $outputDir . "/" . $className . ".h");

  print $fh $copyright;

  print $fh "\n";
  print $fh "\n";
  print $fh "#ifndef ${className}_h\n";
  print $fh "#define ${className}_h\n";
  print $fh "\n";
  print $fh "#include \"IALibrary.h\"\n";
  print $fh "\n";
  print $fh "typedef struct{\n";
  foreach my $attributeLine (@attributeLines){
    print $fh "\t" . $attributeLine . "\n";
  }
  print $fh "} ${className}Ref;\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "static $className * ${className}_createFromYaml(const SampleLayoutAttributes * attr, SampleLayoutRefs * refsOut) {\n";
  foreach my $initLine (@initLines){
    print $fh "\t" . $initLine . "\n";
  }
  print $fh "}\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "\n";
  print $fh "#endif\n";
  print $fh "\n";
  close($fh);

  if (@objectAttributes > 0){

  }

}

sub parseYaml{
  my $yaml = shift;
  my $fh = shift;
  my $context = shift;
  my $contextParams = @_;

  if (ref $yaml eq 'HASH'){
    print $fh "Hash Begin:\n";
    foreach my $key (keys %$yaml){
      print $fh "Key: $key\n";
      printYaml($yaml->{$key}, $fh);
    }
    print $fh "Hash End.\n";
  }elsif (ref $yaml eq 'ARRAY'){
    print $fh "Array Begin:\n";
    foreach my $value (@$yaml){
      printYaml($value, $fh);
    }
    print $fh "Array End.\n";
  }elsif ($yaml and not ref $yaml){
    print $fh "Value: $yaml\n";
  }
}

1;
