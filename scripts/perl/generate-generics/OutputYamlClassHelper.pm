package OutputYamlClassHelper;
use strict;
use warnings FATAL => 'all';

use Expressions;
use Helper;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getParamNamesForYamlNode canCompleteYamlNames canCompleteWithAttributes typecast);

sub privateIsSpecialYamlKey{
  my $key = shift;
  if ($key =~ m/^__.+__$/){
    return 1;
  }else{
    return 0;
  }
}

sub getParamNamesForYamlNode{
  my $yamlNode = shift;
  my @yamlNames = ();
  foreach my $key (keys %$yamlNode){
    if (not privateIsSpecialYamlKey($key)){
      if ($key =~ m\^$matchName->$matchName$\) {
        my $matchedYamlName = $1;
        push @yamlNames, $matchedYamlName;
      }else{
        push @yamlNames, $key;
      }
    }
  }
  return @yamlNames;
}

sub canCompleteYamlNames{
  my $yamlNamesRef = shift;
  my $requiredNamesRef = shift;
  my $optionalNamesRef = shift // \();
  my @yamlNames = @$yamlNamesRef;

  foreach my $requiredName (@$requiredNamesRef){
    my $wasRequiredNameFound = 0;
    foreach my $index (0 .. $#yamlNames){
      if ($requiredName eq $yamlNames[$index]){
        splice @yamlNames, $index, 1;
        $wasRequiredNameFound = 1;
        last;
      }
    }
    if ($wasRequiredNameFound == 0) {
      return 0;
    }
  }
  foreach my $yamlName (@yamlNames){
    my $isYamlNameInOptionalNames = 0;
    foreach my $optionalName (@$optionalNamesRef){
      if ($yamlName eq $optionalName) {
        $isYamlNameInOptionalNames = 1;
        last;
      }
    }
    if ($isYamlNameInOptionalNames == 0) {
      return 0;
    }
  }
  return 1;
}

#Returns an attribute init function or undef
sub canCompleteWithAttributes{
  my $classProvider = shift;
  my $attributeClass = shift;
  my $yamlNamesRef = shift;
  my $requiredNamesRef = shift;

  my @optionalAttributeNames = ();
  foreach my $class ($attributeClass, $classProvider->getAllSuperClassesOfClass($attributeClass)){
    foreach my $setterName ($class->getAllSetterAttributeNames()){
      push @optionalAttributeNames, $setterName;
    }
  }

  foreach my $class ($attributeClass, $classProvider->getAllSuperClassesOfClass($attributeClass)){
    foreach my $attributeClassFunction ($class->getAllNonSpecialValidFunctions()){
      my $functionName = $attributeClassFunction->{name};
      if ($functionName =~ m/^set(.*?)(Function)?$/) {
        my $attributeName = lcfirst $1;
        push @optionalAttributeNames, $attributeName;
      }
    }
  }

  my @attributeInitFunctions = $attributeClass->getValidInitFunctions();
  if (@attributeInitFunctions == 0) {
    @attributeInitFunctions = $attributeClass->getValidMakeFunctions();
  }
  foreach my $localAttributeInitFunction (@attributeInitFunctions){
    my $attributeInitFunctionParams = $localAttributeInitFunction->{params};
    $attributeInitFunctionParams = removeFirstParamFromParams($attributeInitFunctionParams);
    $attributeInitFunctionParams = normalizeParams($attributeInitFunctionParams);
    my @params = listAllParams($attributeInitFunctionParams);
    my @requiredAttributeNamesTemp = ();
    foreach my $param(@params){
      if (not $param =~ m/void\s*\*\s*correspondingObject$/) {
        push @requiredAttributeNamesTemp, getParamName($param);
      }
    }
    push @requiredAttributeNamesTemp, @$requiredNamesRef;
    if (canCompleteYamlNames($yamlNamesRef, \@requiredAttributeNamesTemp, \@optionalAttributeNames)) {
      return $localAttributeInitFunction;
    }
  }
  return undef;
}

sub typecast{
  my $expression = shift;
  my $fromClassName = shift;
  my $toClassName = shift;
  my $classProvider = shift;
  my $yamlFileForLogging = shift;
  my $currentClass = $classProvider->getClass($fromClassName);
  if (not defined $currentClass) {
    die sprintf("Cannot cast from \"%s\" to \"%s\". Reason: Cannot find class \"%s\". Error parsing yaml file \"%s\".", $fromClassName, $toClassName, $fromClassName, $yamlFileForLogging);
  }
  my $count = 0;
  while($currentClass->isObject()){
    my $className = $currentClass->getClassName();
    if ($className eq $toClassName) {
      return "($toClassName *) $expression";
    }
    $count += 1;
    if ($count > 1000){
      die sprintf("Cannot cast from \"%s\" to \"%s\". Reason: max hierarchy length reached. Error parsing yaml file \"%s\".", $fromClassName, $toClassName, $yamlFileForLogging);
    }
    my $superClassName = $currentClass->getSuperClassName();
    if ($superClassName eq "IAObject") {
      last;
    }
    $currentClass = $classProvider->getClass($superClassName);
  }
  die sprintf("Cannot cast from \"%s\" to \"%s\". Class \"%s\" is not a child of \"%s\" . Error parsing yaml file \"%s\".", $fromClassName, $toClassName, $fromClassName, $toClassName, $yamlFileForLogging);
}

1;
