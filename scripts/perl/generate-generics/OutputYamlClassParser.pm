package OutputYamlClassParser;

use strict;
use warnings FATAL => 'all';

use Constants;
use Expressions;
use Function;
use Helper;
use OutputYamlClassHelper;
use ObjectReference;

sub new{
  my $class = shift;
  my $classProvider = shift;
  my $resourceProviders = shift;
  my $attributesClassName = shift;
  my $yamlFilePath = shift;
  my $self = {
    classProvider => $classProvider,
    resourceProviders => $resourceProviders,
    includes => {},
    attributesClassName => $attributesClassName,

    isCorrespondingObjectNeeded => 0,
    objectReferences => {},

    anonymousAttrCount => 0,
    anonymousObjCount => 0,
    anonymousObjRefCount => 0,
    anonymousArrayCount => 0,

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
      my @yamlNames = getParamNamesForYamlNode($yaml);
      my @structMakeFunctions = $class->getMakeFunctionsForStruct();
      foreach my $structMakeFunction (@structMakeFunctions){
        my $functionParams = $structMakeFunction->{params};
        $functionParams = normalizeParams($functionParams);
        my @paramNames = listAllParamNames($functionParams);
        my @params = listAllParams($functionParams);
        if (canCompleteYamlNames(\@yamlNames, \@paramNames)) {
          my %paramExpressions = ();
          foreach my $param (@params){
            my $paramName = getParamName($param);
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
    if ($typeExpected =~ m/char\s*\*$/) {
      return convertYamlScalarToString($yaml);
    }else{
      if ($yaml =~ m/^(\w[\w\d]*)_(\w[\w\d]*)$/){
        $self->privateAddInclude($1);
        return $yaml;
      }elsif ($typeExpected =~ m/^\w[\w\d]*$/ and $isDataTyp == 0) {
        $self->privateAddInclude($typeExpected);
        return $typeExpected . "_" . $yaml;
      }else{
        return $yaml;
      }
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
  my $paramNameForLogging = shift;
  die "Expected string for param \"$paramNameForLogging\". Error parsing yaml file \"" . $self->{yamlFilePath} . "\"." if (not defined $yaml or ref $yaml);
  my $string = convertYamlScalarToString($yaml);
  return $string;
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
  die "Class \"$className\" is not found. Error parsing yaml file \"" . $self->{yamlFilePath} . "\"." if(not defined $class);
  die "Class \"$className\" is not a valid object. It should be a derivative of \"IAObject\". Error parsing yaml file \"" . $self->{yamlFilePath} . "\"." if($variableName eq "" && not $class->isObject());

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
    my $canCompleteParams = 0;
    foreach my $param (listAllParams($initFunctionParams)) {
      if ($wasAttributesAlreadyParsed) {
        die "Invalid parameter order. " .
          "Expected Attributes to be the last parameter for class \"${className}\" in yaml file \""
          . $self->{yamlFilePath} . "\".";
      }
      if ($param =~ m/$matchType\s*$matchName/) {
        my $type = $1;
        my $paramName = $2;
        if ($type =~ m/(^| )$attributeClassName(\$| )/) {
          if (not defined $attributeClass) {
            die "Cannot find attribute class \"$attributeClassName\" for class \"$className\".";
          }
          $attributeInitFunction = canCompleteWithAttributes($classProvider, $attributeClass, \@yamlNames, \@requiredAttributeNames);
          $wasAttributesAlreadyParsed = 1;
          if (defined $attributeInitFunction) {
            $canCompleteParams = 1;
          }
        }else{
          push @requiredAttributeNames, $paramName;
        }
      }else{
        if (not $param =~ m/$matchFunction/){
          die "Internal error. Invalid matched param \"$param\" in yaml file \""
            . $self->{yamlFilePath} . "\".";
        }
        push @requiredAttributeNames, $2;
      }
    }
    if ($canCompleteParams == 0) {
      if ($wasAttributesAlreadyParsed == 0 && canCompleteYamlNames(\@yamlNames, \@requiredAttributeNames, \@optionalAttributeNames)) {
        $canCompleteParams = 1;
      }
    }
    if ($canCompleteParams){
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
    if ($params eq "") {
      $params = "no parameters";
    }else{
      $params = "parameters " . $params;
    }
    die "Cannot generate object of type \"$className\" with $params in yaml file \""
      . $self->{yamlFilePath} . "\".";
  }
  return $result;
}

sub parseAsResource{
  my $self = shift;
  my $yaml = shift;
  my $initLinesRef = shift;
  my $deinitLinesRef = shift;

  my $resourceName = $yaml->{__resource__};
  die "Could not find resource provider for name \"$resourceName\" in yaml file \""
    . $self->{yamlFilePath} . "\"." if (not exists $self->{resourceProviders}->{$resourceName});
  my $resourceProvider = $self->{resourceProviders}->{$resourceName};
  my $className = $resourceProvider->getClassName();
  my $function = $resourceProvider->getFunction();
  my $functionParams = $function->{params};
  if ($functionParams ne "void") {
    $functionParams = normalizeParams($functionParams);
  }else{
    $functionParams = "";
  }
  my @paramsForCall = ();

  foreach my $param (listAllParams($functionParams)){
    if ($param =~ m/^$matchType\s*$matchName$/) {
      my $matchedName = $2;
      my $newYaml = $yaml->{$matchedName};
      my $context = getContextForParams($param);
      my $result = $self->parseContextForObject(
        $context,
        $newYaml,
        $initLinesRef,
        $deinitLinesRef,
        $className,
        $param);
      push @paramsForCall, $result;
    }else{
      die "Expected type and name as params. Error in yaml file \"" . $self->{yamlFilePath} . "\".";
    }
  }
  $self->privateAddInclude($className);
  my $params = join(", ", @paramsForCall);
  return $function->getStaticFunctionCallWithParams($className, $params);
}

sub privateGetAttributeClassName{
  my $className = shift;
  return $className . "Attributes";
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

  $self->privateAddInclude($className);

  my $objectReference = undef;
  my $objectReferenceName = "";
  if (exists $yaml->{__ref__}) {
    $objectReferenceName = $yaml->{__ref__};
    $objectReference = ObjectReference->new($objectReferenceName, $className);
    if (exists $self->{objectReferences}->{$objectReferenceName}) {
      die "References must be unique: Duplicated reference name \"$objectReferenceName\". Error parsing yaml file \"" . $self->{yamlFilePath} . "\".";
    }else{
      $self->{objectReferences}->{$objectReferenceName} = $objectReference;
    }
  }

  my $attributeClassName = privateGetAttributeClassName($className);
  my $attributeClass = $self->{classProvider}->getClass($attributeClassName);
  my @selfInitLines = ();
  my @selfDeinitLines = ();
  my @paramsForNewFunction = ();
  foreach my $param (listAllParams($initFunction->{params})) {
    my $isAttributes = 0;
    if ($param =~ m/^$matchType\s*$matchName$/) {
      my $matchedType = $1;
      if ($matchedType =~ m/(^| )$attributeClassName(\$| )/) {
        $isAttributes = 1;
        my $attributeName = "IA_attr" . $self->{anonymousAttrCount};
        $self->{anonymousAttrCount} += 1;
        push @selfInitLines, "\t$attributeClassName $attributeName;\n";
        my @paramsForInitAttributesFunction = ("&" . $attributeName);
        my $attributeInitParams = $attributeInitFunction->{params};
        $attributeInitParams = removeFirstParamFromParams($attributeInitParams);
        $attributeInitParams = normalizeParams($attributeInitParams);
        foreach my $attributeInitParam (listAllParams($attributeInitParams)){
          if ($attributeInitParam =~ m/^$matchType\s*$matchName$/) {
            my $attributeParamMatchedType = $1;
            my $attributeParamMatchedName = $2;
            if (exists $yaml->{$attributeParamMatchedName}) {
              my $newYaml = $yaml->{$attributeParamMatchedName};
              my $context = getContextForParams($attributeInitParam);
              my $result = $self->parseContextForObject(
                $context,
                $newYaml,
                \@selfInitLines,
                \@selfDeinitLines,
                $className,
                $attributeInitParam);
              push @paramsForInitAttributesFunction, $result;
            }elsif ($attributeParamMatchedType =~ m/void\s*\*$/ and $attributeParamMatchedName eq "correspondingObject"){
              $self->{isCorrespondingObjectNeeded} = 1;
              push @paramsForInitAttributesFunction, $self->{attributesClassName}. "_getCorrespondingObject(attr)";
            }else{
              die "Cannot parse type and name as params for attributes init function. Error in yaml file \"" . $self->{yamlFilePath} . "\".";
            }
          }else{
            die "Expected type and name as params. Error in yaml file \"" . $self->{yamlFilePath} . "\".";
          }
        }
        push @selfInitLines, "\t" . $attributeInitFunction->getFunctionCallWithParams($attributeClassName, join(", ", @paramsForInitAttributesFunction)) . ";\n";
        push @paramsForNewFunction, "&" . $attributeName;
        if ($attributeInitFunction->isInitFunction()) {
          my $attributeDeinitFunction = $attributeClass->getDeinitFunction();
          die "Attribute class \"$attributeClassName\" has init but no deinit function." if (not defined $attributeDeinitFunction);
          push @selfDeinitLines, "\t". $attributeDeinitFunction->getFunctionCallWithParams($attributeClassName,"&" . $attributeName) . ";\n";
        }

        my @setterFunctions = ();

        foreach my $class ($attributeClass, $self->{classProvider}->getAllSuperClassesOfClass($attributeClass)){
          foreach my $function ($class->getAllNonSpecialValidFunctions()){
            my $functionName = $function->{name};
            if ($functionName =~ m/^set/) {
              push @setterFunctions, $function;
            }
          }

          foreach my $setterName(@{$class->{setters}}){
            my $attribute = $class->getAttribute($setterName);
            my $printable = $attribute->getSetterPrintable($attributeClassName, "IA_this");
            my $function = Function->new();
            $function->initWithHeader($attributeClassName, $printable, "");
            push @setterFunctions, $function;

          }
          foreach my $setterName(@{$class->{settersAsRef}}){
            my $attribute = $class->getAttribute($setterName);
            my $printable = $attribute->getSetterAsRefPrintable($attributeClassName, "IA_this");
            my $function = Function->new();
            $function->initWithHeader($attributeClassName, $printable, "");
            push @setterFunctions, $function;

          }
          foreach my $setterName(@{$class->{settersAsCharArray}}){
            my $attribute = $class->getAttribute($setterName);
            my $printable = $attribute->getSetterAsCharArrayPrintable($attributeClassName, "IA_this");
            my $function = Function->new();
            $function->initWithHeader($attributeClassName, $printable, "");
            push @setterFunctions, $function;
          }
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
        if (defined $objectReference) {
          $objectReference->makeInjectable($attributeClassName);
          push @selfInitLines, sprintf("\t%s_onInject%s(attr, %s);\n", $self->{attributesClassName}, ucfirst $objectReferenceName, "&" . $attributeName);
        }
      }
    }
    if ($isAttributes == 0) {
      if ($param =~ m/^$matchType\s*$matchName$/) {
        my $matchedName = $2;
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
        die "Expected type and name as params. Error in yaml file \"" . $self->{yamlFilePath} . "\".";
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
  if (defined $objectReference) {
    my $tempVarName = "IA_objRef" . $self->{anonymousObjRefCount};
    $self->{anonymousObjRefCount} += 1;
    push @$initLinesRef, "\t$className ** $tempVarName = " . $self->{attributesClassName} . "_get" . ucfirst($objectReferenceName) . "Ref(attr);\n";
    push @$initLinesRef, "\tif ($tempVarName != NULL) {\n";
    push @$initLinesRef, "\t\t*$tempVarName = $variableName;\n";
    push @$initLinesRef, "\t}\n";
  }
  return $variableName;
}

sub getContextForParams{
  my @params = @_;

  if (scalar @params == 1) {
    if ($params[0] =~ m/^$matchType\s*$matchName$/) {
      my $matchedType = $1;
      if ($matchedType =~ m/char\s*\*$/) {
        return "STRING";
      }elsif ($matchedType =~ m/\*$/){
        return "OBJECT";
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
  my $classNameForLogging = shift;
  my @params = @_;

  if ($context eq "OBJECT") {
    my $forceType = "";
    if (ref $yaml eq "HASH" and exists $yaml->{__type__}) {
      $forceType = $yaml->{__type__};
    }

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
      if (exists $yaml->{__resource__}) {
        my $result = $self->parseAsResource($yaml, $initLinesRef, $deinitLinesRef);
        my $resourceProvider = $self->{resourceProviders}->{$yaml->{__resource__}};
        my $function = $resourceProvider->getFunction();
        my $returnType = $function->{returnType};
        $returnType =~ m/$matchName/;
        my $className = $1;
        $result = typecast($result, $className, $orgType, $self->{classProvider}, $self->{yamlFilePath});
        return $result;
      }else{
        my $result = $self->parseObject($expectedType, $yaml, $initLinesRef, $deinitLinesRef);
        $result = typecast($result, $expectedType, $orgType, $self->{classProvider}, $self->{yamlFilePath});
        return $result;
      }
    }else {
      die "Unsupported type \"$expectedType\" for \"OBJECT\"-context in class \"$classNameForLogging\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
    }
  }elsif($context eq "EXPRESSION") {
    $params[0] =~ m/^$matchType\s*$matchName$/ or die "Expected type and name for \"EXPRESSION\"-context in class \"$classNameForLogging\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
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
      die "Unsupported type \"$expectedType\" for \"ARRAY\"-context in class \"$classNameForLogging\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
    }
  }elsif($context eq "FUNCTION") {
    die "Function pointers are not supported yet in class \"$classNameForLogging\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
  }elsif($context eq "STRING"){
    $params[0] =~ m/$matchType\s*$matchName/;
    my $paramName = $2;
    return $self->parseString($yaml, $paramName);
  }else {
    die "Could not parse context \"$context\" in class \"$classNameForLogging\" parsing yaml file \"" . $self->{yamlFilePath} . "\".";
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

sub privateAddInclude{
  my $self = shift;
  my $classNameToInclude = shift;
  $self->{includes}->{$classNameToInclude} = $classNameToInclude;
}

1;