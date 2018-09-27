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
use OutputHeaderFile;

sub printFromYamlToFile{
  my $class = shift;
  my $classProvider = shift;
  my $resourceProviders = shift;
  my $outputDir = shift;

  die "Cannot printFromYamlToFile with not an yaml class \"" . $class->getClassName() . "\"." if (not $class->{yaml});

  my $className = $class->getClassName();
  my $attributesClassName =  $className . "Attributes";
  my $yaml = $class->{yaml};

  return if (exists $yaml->{__template__});

  my $parser = OutputYamlClassParser->new($classProvider, $resourceProviders, $attributesClassName, $class->{filePath});

  my $classnameToGenerate = $class->{yaml}->{__generate__};
  my @initLines = ();
  my @deinitLines = ();
  my $result = $parser->parseObject($classnameToGenerate, $yaml, \@initLines, \@deinitLines, "this");
  die "Expected \"this\" as a result, got \"$result\"." if ($result ne "this");

  my %objectReferences = %{$parser->{objectReferences}};
  my $hasAttributes = 0;
  if (keys %objectReferences > 0) {
    $hasAttributes = 1;
  }elsif ($parser->{isCorrespondingObjectNeeded}){
    $hasAttributes = 1;
  }

  my $fileName = $outputDir . "/" . $className . ".h";
  open(my $fh, ">", $fileName) or die "Could not open file \"$fileName\".";
  print $fh $copyright;
  print $fh "\n";
  print $fh "\n";
  print $fh "#ifndef ${className}_h\n";
  print $fh "#define ${className}_h\n";
  print $fh "\n";
  print $fh "#include \"IALibrary.h\"\n";
  if ($hasAttributes) {
    print $fh "#include \"$attributesClassName.h\"\n";
  }else{
    foreach my $include (sort keys %{$parser->{includes}}){
      print $fh "#include \"$include.h\"\n";
    }
  }
  print $fh "\n";
  my $additionalParamsForInit = "";
  my $additionalParamsForNew = "";
  my $additionalParamsForInitCall = "";
  if ($hasAttributes) {
    $additionalParamsForInit = ", const $attributesClassName * attr";
    $additionalParamsForNew = "const $attributesClassName * attr";
    $additionalParamsForInitCall = ", attr";
  }
  my $initMethodName = "initFromYaml";
  my $deinitMethod = "${classnameToGenerate}_deinit";
  if (@deinitLines == 0) {
    $initMethodName = "makeFromYaml";
    $deinitMethod = "NULL";
  }
  print $fh "static inline void ${className}_$initMethodName($classnameToGenerate * this$additionalParamsForInit) {\n";
  foreach my $initLine (@initLines){
    print $fh $initLine;
  }
  print $fh "}\n";
  print $fh "\n";
  print $fh "static inline $classnameToGenerate * ${className}_newFromYaml($additionalParamsForNew) {\n";
  print $fh "\t$classnameToGenerate * this = IA_newWithClassName(sizeof($classnameToGenerate), (void (*)(void *)) $deinitMethod, \"$classnameToGenerate\");\n";
  print $fh "\t${className}_$initMethodName(this$additionalParamsForInitCall);\n";
  print $fh "\treturn this;\n";
  print $fh "}\n";
  print $fh "\n";
  print $fh "static inline $classnameToGenerate * ${className}_fromYaml($additionalParamsForNew) {\n";
  print $fh "\t$classnameToGenerate * this = IA_newWithClassName(sizeof($classnameToGenerate), (void (*)(void *)) $deinitMethod, \"$classnameToGenerate\");\n";
  print $fh "\t${className}_$initMethodName(this$additionalParamsForInitCall);\n";
  print $fh "\tIA_autorelease(this);\n";
  print $fh "\treturn this;\n";
  print $fh "}\n";
  print $fh "\n";
  print $fh "#endif\n";
  print $fh "\n";
  close($fh);

  if ($hasAttributes) {
    my $attributesFileName = $outputDir . "/" . $attributesClassName . ".h";
    open($fh, ">", $attributesFileName) or die "Could not open file \"$attributesFileName\".";
    print $fh $copyright;
    print $fh "\n";
    print $fh "\n";
    print $fh "#ifndef ${attributesClassName}_h\n";
    print $fh "#define ${attributesClassName}_h\n";
    print $fh "\n";
    foreach my $include (sort keys %{$parser->{includes}}){
      print $fh "#include \"$include.h\"\n";
    }
    print $fh "\n";
    print $fh "typedef struct $attributesClassName $attributesClassName;\n";
    print $fh "struct ${attributesClassName}{\n";
    print $fh "\t//\@set+get\n";
    print $fh "\tvoid * correspondingObject;\n";
    foreach my $objectReferenceKey (sort keys %objectReferences){
      my $objectReference = $objectReferences{$objectReferenceKey};
      print $fh "\t//\@set+get\n";
      print $fh "\t" . $objectReference->getType() . " ** " . $objectReference->getRefName() . "Ref;\n";
      if ($objectReference->isInjectable()) {
        print $fh "\t//\@set+exe\n";
        print $fh "\tvoid (*onInject" .  ucfirst($objectReference->getRefName()) . ")("
          . "void * correspondingObject, "
          . "$classnameToGenerate * " . lcfirst ($className) . ", "
          . $objectReference->getAttributesClassNameForInjection() . " * attr);\n";
      }
    }
    print $fh "};\n";
    print $fh "\n";
    print $fh "static inline void ${attributesClassName}_make(${attributesClassName} * this, void * correspondingObject){\n";
    print $fh "\t*this = (${attributesClassName}){\n";
    print $fh "\t\t.correspondingObject = correspondingObject\n";
    print $fh "\t};\n";
    print $fh "}\n";
    print $fh "\n";
    print $fh "#include \"${attributesClassName}+Generated.h\"\n";
    print $fh "\n";
    print $fh "#endif\n";
    print $fh "\n";
    print $fh "\n";
    close($fh);

    $classProvider->addHeaderFile($attributesFileName);
    $class = $classProvider->getClass($attributesClassName);
    printHeaderFilesForClass($class, $classProvider, $outputDir);
  }
}

1;
