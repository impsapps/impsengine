package OutputYamlClassParser;

use strict;
use warnings FATAL => 'all';

use Constants;
use Expressions;
use Function;
use Helper;
use OutputYamlClassHelper;

sub new{
  my $class = shift;
  my $classProvider = shift;
  my $yamlFilePath = shift;
  my $self = {
    classProvider => $classProvider,
    includes => {},

    objectReferences => [],

    anonymousAttrCount => 0,
    anonymousObjCount => 0,
    anonymousArrayCount => 0,
    anonymousFunctionCount => 0,

    yamlFilePath => $yamlFilePath
  };
  bless $self, $class;
  return $self;
}

sub parseExpression{
  my $self = shift;
  my $typeExpected = shift;
  my $yaml = shift;
  my $classProvider = $self->{classProvider};

  my $class = undef;
  my $isDataTyp = 0;
  if ($typeExpected =~ m/^\w[\w\d]*$/) {
    $class = $classProvider->getClass($typeExpected);
    if (not defined $class) {
      $isDataTyp = 1;
    }
  }

  if (ref $yaml eq 'HASH'){
    if (defined $class) {
      my @structMakeFunctions = $class->getMakeFunctionsForStruct();
      foreach my $structMakeFunction (@structMakeFunctions){
        my $functionParams = $structMakeFunction->{params};
        $functionParams = normalizeParams($functionParams);
        my @paramNames = listAllParamNames($functionParams);
        my @params = listAllParams($functionParams);
        if (canCompleteYamlNames($yaml, \@paramNames)) {
          my %paramExpressions = ();
          foreach my $param (@params){
            my $paramName = convertParamToValue($param);
            $paramExpressions{$paramName} = $self->parseExpressionForStruct($param, $yaml->{$paramName}, $class->getClassName());
          }
          my $expr = $class->getClassName() . "_" . $structMakeFunction->{name} . "(";
          my $isFirst = 1;
          foreach my $paramName (@paramNames){
            if ($isFirst == 0) {
              $expr = $expr . ", ";
            }
            $expr = $expr . $paramExpressions{$paramName};
            $isFirst = 0;
          }
          $expr = $expr . ")";
          return $expr;
        }
      }
    }
    die "Could not parse expression with yaml hash. Expected type \"$typeExpected\" in \"" . $self->{yamlFilePath} . "\".";
  }elsif (ref $yaml eq 'ARRAY'){
    if (defined $class) {
      my @attributeNames = @{$class->{allAttributeNames}};
      if (scalar @attributeNames == scalar @$yaml) {
        my $expr = "(" . $class->getClassName() . ") {";
        foreach my $index (0 .. $#attributeNames){
          my $attributeName = $attributeNames[$index];
          my $attribute = $class->getAttribute($attributeName);
          if ($index > 0) {
            $expr = $expr . ", ";
          }
          my $attributeParam = $attribute->{type} . " " . $attribute->{name};
          $expr = $expr . $self->parseExpressionForStruct($attributeParam, $yaml->[$index], $class->getClassName());
        }
        $expr = $expr . "}";
        return $expr;
      }
    }
    die "Could not parse expression with yaml array. Expected type \"$typeExpected\" in \"" . $self->{yamlFilePath} . "\".";
  }elsif (defined $yaml and not ref $yaml){
    if ($typeExpected =~ m/^\w[\w\d]*$/ and $isDataTyp == 0) {
      $self->{includes}->{$typeExpected} = $typeExpected;
      return $typeExpected . "_" . $yaml;
    }else{
      return $yaml;
    }
  }
  die "Yaml parse error. Unknown Type in file \"" . $self->{yamlFilePath} . "\".";
}

sub parseExpressionForStruct{
  my $self = shift;
  my $param = shift;
  my $yaml = shift;
  my $className = shift;
  if ($param =~ m/^$matchType\s+$matchName$/) {
    my $typeExpected = $1;
    return $self->parseExpression($typeExpected, $yaml);
  }else{
    die "Could not parse param \"$param\" in class \"$className\" for struct in \"" . $self->{yamlFilePath} . "\".";
  }
}

sub parseString{
  my $self = shift;
  my $yaml = shift;
  return $yaml;
}

sub parseObject{
  my $self = shift;
  my $className = shift;
  my $yaml = shift;
  my $initLinesRef = shift;
  my $deinitLinesRef = shift;
  my $variableName = shift // "";

  if (defined $yaml and not ref $yaml) {
    return $self->parseExpression("$className *", $yaml);
  }

  my $classProvider = $self->{classProvider};

  my $class = $classProvider->getClass($className);
  my $attributeClassName = privateGetAttributeClassName($className);
  my $attributeClass = $classProvider->getClass($attributeClassName);
  die "Class \"$className\" does not extend from \"IAObject\" which was expected. Error parsing yaml file \"" . $class->getFilePath() . "\"." if($variableName eq "" && not $class->isObject());

  my @yamlNames = getParamNamesForYamlNode($yaml);

  my @initFunctions = $class->getValidInitFunctions();
  if (@initFunctions == 0) {
    @initFunctions = $class->getValidMakeFunctions();
  }
  my $result = undef;
  foreach my $initFunction (@initFunctions){
    my $initFunctionParams = $initFunction->{params};
    $initFunctionParams = removeFirstParamFromParams($initFunctionParams);
    $initFunctionParams = normalizeParams($initFunctionParams);
    my @requiredAttributeNames = ();
    my @optionalAttributeNames = ();
    my $wasAttributesAlreadyParsed = 0;
    my $attributeInitFunction = undef;
    while ($initFunctionParams =~ m/$matchSingleNormalizedParam/g) {
      my $param = $1;
      if ($wasAttributesAlreadyParsed) {
        die "Invalid parameter order. " .
          "Expected Attributes to be the last parameter for class \"${className}\" in yaml file \""
          . $class->getFilePath() . "\".";
      }
      if ($param =~ m/$matchType\s*$matchName/) {
        my $type = $1;
        my $paramName = $2;
        if ($type =~ m/(^| )$attributeClassName(\$| )/) {
          if (not defined $attributeClass) {
            die "Cannot find attribute class \"$attributeClassName\" for class \"$className\".";
          }
          $attributeInitFunction = canCompleteWithAttributes($attributeClass, \@yamlNames, \@requiredAttributeNames);
          $wasAttributesAlreadyParsed = 1;
        }else{
          push @requiredAttributeNames, $paramName;
        }
      }else{
        if (not $param =~ m/$matchFunction/){
          die "Internal error. Invalid matched param \"$param\" in yaml file \""
            . $class->getFilePath() . "\".";
        }
        push @requiredAttributeNames, $2;
      }
    }
    if (defined $attributeInitFunction || canCompleteYamlNames(\@yamlNames, \@requiredAttributeNames, \@optionalAttributeNames)){
      $result = $self->parseObjectWithFunctions(
        $className,
        $yaml,
        $initLinesRef,
        $deinitLinesRef,
        $variableName,
        $initFunction,
        $attributeInitFunction);
      last;
    }
  }
  if (not defined $result){
    my $params = "";
    foreach my $index (0 .. $#yamlNames){
      my $param = $yamlNames[$index];
      $param = '"' . $param . '"';
      if (length $params > 0) {
        if ($index == $#yamlNames) {
          $params = $params . " and " . $param;
        }else{
          $params = $params . ", " . $param;
        }
      }else{
        $params = $param;
      }
    }
    die "Cannot generate object of type \"$className\" with parameters $params in yaml file \""
      . $self->{yamlFilePath} . "\".";
  }
  return $result;
}

sub privateGetAttributeClassName{
  my $className = shift;
  return $className . "Attributes";
}

#Returns an attribute init function or undef
sub canCompleteWithAttributes{
  my $attributeClass = shift;
  my $yamlNamesRef = shift;
  my $requiredNamesRef = shift;

  my @optionalAttributeNames = ();
  foreach my $setterName ($attributeClass->getAllSetterAttributeNames()){
    push @optionalAttributeNames, $setterName;
  }
  foreach my $attributeClassFunction ($attributeClass->getAllNonSpecialValidFunctions()){
    my $functionName = $attributeClassFunction->{name};
    if ($functionName =~ m/^set(.*?)(Function)?$/) {
      my $attributeName = lcfirst $1;
      push @optionalAttributeNames, $attributeName;
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
    my @requiredAttributeNamesTemp = listAllParamNames($attributeInitFunctionParams);
    push @requiredAttributeNamesTemp, @$requiredNamesRef;
    if (canCompleteYamlNames($yamlNamesRef, \@requiredAttributeNamesTemp, \@optionalAttributeNames)) {
      return $localAttributeInitFunction;
    }
  }
  return undef;
}

sub parseObjectWithFunctions{
  my $self = shift;
  my $className = shift;
  my $yaml = shift;
  my $initLinesRef = shift;
  my $deinitLinesRef = shift;
  my $variableName = shift;
  my $initFunction = shift;
  my $attributeInitFunction = shift // undef;

  $self->{includes}->{$className} = $className;

  my $attributeClassName = privateGetAttributeClassName($className);
  my $attributeClass = $self->{classProvider}->getClass($attributeClassName);
  my @selfInitLines = ();
  my @selfDeinitLines = ();
  my @paramsForNewFunction = ();
  while ($initFunction->{params} =~ m/$matchSingleNormalizedParam/g) {
    my $param = $1;
    my $isAttributes = 0;
    if ($param =~ m/^$matchType\s*$matchName$/) {
      my $matchedType = $1;
      if ($matchedType =~ m/(^| )$attributeClassName(\$| )/) {
        $isAttributes = 1;
        my $attributeName = "IA_attr" . $self->{anonymousAttrCount};
        $self->{anonymousAttrCount} += 1;
        push @selfInitLines, "\t$attributeClassName $attributeName;\n";
        push @selfInitLines, "\t" . $attributeInitFunction->getFunctionCallWithParams($attributeClassName, "&" . $attributeName) . ";\n";
        push @paramsForNewFunction, "&" . $attributeName;
        if ($attributeInitFunction->isInitFunction()) {
          my $attributeDeinitFunction = $attributeClass->getDeinitFunction();
          die "Attribute class \"$attributeClassName\" has init but no deinit function." if (not defined $attributeDeinitFunction);
          push @selfDeinitLines, "\t". $attributeDeinitFunction->getFunctionCallWithParams($attributeClassName,"&" . $attributeName) . ";\n";
        }

        my @setterFunctions = ();
        foreach my $function ($attributeClass->getAllNonSpecialValidFunctions()){
          my $functionName = $function->{name};
          if ($functionName =~ m/^set/) {
            push @setterFunctions, $function;
          }
        }

        foreach my $setterName(@{$attributeClass->{setters}}){
          my $attribute = $attributeClass->getAttribute($setterName);
          my $printable = $attribute->getSetterPrintable($attributeClassName, "this");
          my $function = Function->new();
          $function->initWithHeader($attributeClassName, $printable, "");
          push @setterFunctions, $function;

        }
        foreach my $setterName(@{$attributeClass->{settersAsRef}}){
          my $attribute = $attributeClass->getAttribute($setterName);
          my $printable = $attribute->getSetterAsRefPrintable($attributeClassName, "this");
          my $function = Function->new();
          $function->initWithHeader($attributeClassName, $printable, "");
          push @setterFunctions, $function;

        }
        foreach my $setterName(@{$attributeClass->{settersAsCharArray}}){
          my $attribute = $attributeClass->getAttribute($setterName);
          my $printable = $attribute->getSetterAsCharArrayPrintable($attributeClassName, "this");
          my $function = Function->new();
          $function->initWithHeader($attributeClassName, $printable, "");
          push @setterFunctions, $function;
        }

        foreach my $setterFunction (@setterFunctions){
          my $setterFunctionParams = $setterFunction->{params};
          $setterFunctionParams = removeFirstParamFromParams($setterFunctionParams);
          $setterFunctionParams = normalizeParams($setterFunctionParams);

          my $setterFunctionName = $setterFunction->{name};
          my $setterName = $setterFunctionName;
          $setterName =~ s/^set(.*?)(Function)?$/$1/;
          $setterName = lcfirst $setterName;

          if (exists $yaml->{$setterName}) {
            my $newYaml = $yaml->{$setterName};
            my @params = listAllParams($setterFunctionParams);
            my $context = getContextForParams(@params);
            my $result = $self->parseContextForObject(
              $context,
              $newYaml,
              \@selfInitLines,
              \@selfDeinitLines,
              $className,
              @params);
            push @selfInitLines, "\t" . $setterFunction->getFunctionCallWithParams($attributeClassName, "&" . $attributeName, $result) . ";\n";
          }
        }
      }
    }
    if ($isAttributes == 0) {
      my $matchedName = $2;
      if ($param =~ m/^$matchType\s*$matchName$/) {
        $matchedName = $2;
        my $newYaml = $yaml->{$matchedName};
        my $context = getContextForParams($param);
        my $result = $self->parseContextForObject(
          $context,
          $newYaml,
          \@selfInitLines,
          \@selfDeinitLines,
          $className,
          $param);
        push @paramsForNewFunction, $result;
      }else{
        die "Expected type and name as params.";
      }
    }
  }

  if ($variableName eq "") {
    my $newFunctionName = convertFunctionNameForNew($initFunction->{name});
    $variableName = "IA_obj" . $self->{anonymousObjCount};
    $self->{anonymousObjCount} += 1;
    push @$initLinesRef, @selfInitLines;
    push @$initLinesRef, "\t$className * $variableName = ${className}_${newFunctionName}(" . join(", ", @paramsForNewFunction) . ");\n";
    push @$initLinesRef, @selfDeinitLines;
    push @$deinitLinesRef, "\t${className}_release($variableName);\n";
  }else{
    my $functionName = $initFunction->{name};
    push @$initLinesRef, @selfInitLines;
    push @$initLinesRef, "\t${className}_${functionName}(" . join(", ", $variableName, @paramsForNewFunction) . ");\n";
    push @$initLinesRef, @selfDeinitLines;
    if ($initFunction->isInitFunction()) {
      push @$deinitLinesRef, "\t${className}_deinit($variableName);\n";
    }
  }
  return $variableName;
}

sub getContextForParams{
  my @params = @_;

  if (scalar @params == 1) {
    if ($params[0] =~ m/^$matchType\s*$matchName$/) {
      my $matchedType = $1;
      if ($matchedType =~ m/\*$/) {
        return "OBJECT";
      }elsif ($matchedType =~ m/\s+char\s*\*$/){
        return "STRING";
      }else{
        return "EXPRESSION";
      }
    }elsif ($params[0] =~ m/^$matchFunction$/) {
      return "FUNCTION";
    }
  } elsif (scalar @params == 2) {
    if ($params[0] =~ m/^$matchType\s*$matchName$/) {
      my $param0Type = $1;
      my $param0Name = $2;
      if ($params[1] =~ m/^$matchType\s*$matchName$/){
        my $param1Type = $1;
        my $param1Name = $2;
        if($param0Type =~ m/^size_t$/ and $params[1] =~ m/^$param1Type\s*$param1Name\[($param0Name)?\]$/){
          return "ARRAY";
        }
      }
    }
  }
  return "UNKNOWN";
}

sub parseContextForObject{
  my $self = shift;
  my $context = shift;
  my $yaml = shift;
  my $initLinesRef = shift;
  my $deinitLinesRef = shift;
  my $className = shift;
  my @params = @_;
  
  my $forceType = "";
  if (ref $yaml eq "HASH" and exists $yaml->{__type__}) {
    $forceType = $yaml->{__type__};
  }

  if ($forceType ne "" and $context ne "OBJECT") {
    die "Type casting is only allowed in an OBJECT-context. Error in yaml file \"" . $self->{yamlFilePath} . "\".";
  }

  if ($context eq "OBJECT") {
    my $isValid = 0;
    my $orgType = undef;
    my $expectedType = undef;
    if ($params[0] =~ m/$matchType\s*$matchName/) {
      $expectedType = $1;
      if ($expectedType =~ m/^$matchName\s*\*$/) {
        $orgType = $1;
        $expectedType = $1;
        if ($forceType ne "") {
          $expectedType = $forceType;
        }
        $isValid = 1;
      }
    }
    if ($isValid) {
      my $result = $self->parseObject($expectedType, $yaml, $initLinesRef, $deinitLinesRef);
      if ($forceType ne "") {
        $result = "($orgType *) " . $result;
      }
      return $result;
    }else {
      die "Unsupported type \"$expectedType\" for \"OBJECT\"-context in class \"$className\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
    }
  }elsif($context eq "EXPRESSION") {
    $params[0] =~ m/^$matchType\s*$matchName$/ or die "Expected type and name for \"EXPRESSION\"-context in class \"$className\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
    my $typeExpected = $1;
    return $self->parseExpression($typeExpected, $yaml);
  }elsif($context eq "ARRAY") {
    my $isValid = 0;
    my $expectedType = undef;
    if ($params[1] =~ m/$matchType\s*$matchName/) {
      $expectedType = $1;
      if (not $expectedType =~ m/^$matchName\s*\*$/) {
        $isValid = 1;
      }
    }
    if ($isValid) {
      return $self->parseObjectArray($expectedType, $yaml, $initLinesRef, $deinitLinesRef);
    }else {
      die "Unsupported type \"$expectedType\" for \"ARRAY\"-context in class \"$className\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
    }
  }elsif($context eq "FUNCTION") {
    die "Function pointers are not supported yet in class \"$className\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
  }elsif($context eq "STRING"){
    return $self->parseString($yaml);
  }else {
    die "Could not parse context \"$context\" in class \"$className\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
  }
}

sub parseObjectArray{
  my $self = shift;
  my $className = shift;
  my $yaml = shift;
  my $initLinesRef = shift;
  my $deinitLinesRef = shift;

  my $sizeVarName = "IA_arraySize" . $self->{anonymousArrayCount};
  my $arrayVarName = "IA_array" . $self->{anonymousArrayCount};
  $self->{anonymousArrayCount} += 1;

  my $arrayCount = scalar @$yaml;

  push @$initLinesRef, "\tsize_t $sizeVarName = $arrayCount;\n";
  push @$initLinesRef, "\t$className $arrayVarName\[$sizeVarName\];\n";
  foreach my $index (0 .. $#{$yaml}){
    my $newYaml = $yaml->[$index];
    my $variableName = "&$arrayVarName\[$index\]";
    $self->parseObject($className, $newYaml, $initLinesRef, $deinitLinesRef, $variableName);
  }

  return "$sizeVarName, $arrayVarName";
}

1;