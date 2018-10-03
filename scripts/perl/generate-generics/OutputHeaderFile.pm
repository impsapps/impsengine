#!/usr/bin/perl

use strict;
use warnings;

package OutputHeaderFile;

use Constants;
use Helper;
use Function;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getEventNameForClassName printHeaderFilesForClass);


my $genericsClassExtension = "+Generated.h";

my $constructorComment = "// Constructor methods:\n";
my $setterComment = "// Setters:\n";
my $getterComment = "// Getters:\n";
my $respondsToComment = "// Responds to:\n";
my $exeComment = "// Executables:\n";
my $lockComment = "// Lockable:\n";
my $registerComment = "// Register for events:\n";
my $doxygenLinkComment = "// Link functions to class for doxygen:\n";

my $inheritedComment = "// Methods inherited from {CLASSNAME}:\n";
my $inheritedSetterComment = "// Setters inherited from {CLASSNAME}:\n";
my $inheritedGetterComment = "// Getters inherited from {CLASSNAME}:\n";
my $inheritedRespondsToComment = "// Responds to's inherited from {CLASSNAME}:\n";
my $inheritedExeComment = "// Executables inherited from {CLASSNAME}:\n";
my $inheritedLockComment = "// Lockable inherited from {CLASSNAME}:\n";
my $inheritedRegisterComment = "// Register for events inherited from {CLASSNAME}:\n";

my $doxygenExtendComment = "// Link super class for doxygen:\n";

my $memberOfFormat = "/// \\memberof %s\n";
my $functionPrefix = "static inline ";


sub getEventNameForClassName{
  my $className = shift;
  $className =~ s/(Delegate)?$/Event/;
  return $className;
}

sub printHeaderFilesForClass{
  my $class = shift;
  my $classProvider = shift;
  my $genDir = shift;

  my $className = $class->getClassName();
  my $fileName = $className . $genericsClassExtension;
  my $path = $genDir . "/" . $fileName;

  if((not $class) || $class->isValidClass() == 0){
    return;
  }

  my $objectVariableName = $class->getObjectVariableName();

  open HEADER, ">", $path or die "unable to open header file $path for writing!";
  print HEADER $copyright;
  print HEADER "\n\n";

  print HEADER "#include \"IALibrary.h\"\n";
  print HEADER "#include \"IAAutoreleasePool.h\"\n\n\n";

  #generate new functions
  my $isCommented = 0;

  if ($class->isObject()) {
    my $areInitFunctions = 1;
    my @functions = $class->getValidInitFunctions();
    if (@functions == 0){
      $areInitFunctions = 0;
      @functions = $class->getValidMakeFunctions();
    }
    foreach my $function (@functions) {
      if($isCommented == 0){
        print HEADER $constructorComment;
      }
      $isCommented = 1;

      my $functionNameForNew = convertFunctionNameForNew($function->{name});
      my $functionNameForWith = convertFunctionNameForWith($function->{name});

      my $definitionForNew = $className . " * " . $className . "_" . $functionNameForNew;
      my $definitionForWith = $className . " * " . $className . "_" . $functionNameForWith;

      my $params = $function->{params};
      $params = removeFirstParamFromParams($params);
      $params = normalizeParams($params);
      my $valueParams = convertParamsToValues($params);

      my $deinitFunction = "NULL";
      if ($areInitFunctions){
        $deinitFunction = "(void (*)(void *)) " . $className . "_deinit";
      }

      printf HEADER $functionPrefix;
      printf HEADER "%s(%s){\n", $definitionForNew, $params;
      printf HEADER "\t%s * this = IA_newWithClassName(sizeof(%s), %s, \"%s\");\n", $className, $className, $deinitFunction, $className;
      if(length $valueParams == 0){
        printf HEADER "\t%s_%s(this);\n", $className, $function->{name};
      }else{
        printf HEADER "\t%s_%s(this, %s);\n", $className, $function->{name}, $valueParams;
      }
      print HEADER "\treturn this;\n";
      print HEADER "}\n\n";

      printf HEADER $functionPrefix;
      printf HEADER "%s(%s){\n", $definitionForWith, $params;
      printf HEADER "\t%s * this = IA_newWithClassName(sizeof(%s), %s, \"%s\");\n", $className, $className, $deinitFunction, $className;
      if(length $valueParams == 0){
        printf HEADER "\t%s_%s(this);\n", $className, $function->{name};
      }else{
        printf HEADER "\t%s_%s(this, %s);\n", $className, $function->{name}, $valueParams;
      }
      print HEADER "\tIA_autorelease(this);\n";
      print HEADER "\treturn this;\n";
      print HEADER "}\n\n";
    }
  }

  if ($class->isObject() || $class->isDelegate()) {
    printf HEADER $functionPrefix;
    printf HEADER "void %s_retain(%s * this){\n", $className, $className;
    printf HEADER "\tIA_retain(this);\n";
    print HEADER "}\n\n";
  }

  if($isCommented){
    print HEADER "\n";
  }

  #link functions for doxygen
  $isCommented = 0;
  foreach my $function (@{$class->{functions}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $doxygenLinkComment;
    }
    if($function->isMakeFunction() || $function->isInitFunction()){
      print HEADER $function->getDoxygenComment($className, $constructorMacro);
    }elsif(not $function->isDeinitFunction()){
      print HEADER $function->getDoxygenComment($className);
    }
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  #generate setter functions
  $isCommented = 0;
  foreach my $setterAsCharArray(@{$class->{settersAsCharArray}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $setterComment;
    }
    my $attribute = $class->{attributes}->{$setterAsCharArray};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getSetterAsCharArrayImplPrintable($className, $objectVariableName);
  }
  foreach my $setter(@{$class->{setters}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $setterComment;
    }
    my $attribute = $class->{attributes}->{$setter};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getSetterImplPrintable($className, $objectVariableName);
  }
  foreach my $setterAsRef(@{$class->{settersAsRef}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $setterComment;
    }
    my $attribute = $class->{attributes}->{$setterAsRef};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getSetterAsRefImplPrintable($className, $objectVariableName);
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  #generate getter functions
  $isCommented = 0;
  foreach my $getterAsCharArray(@{$class->{gettersAsCharArray}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $getterComment;
    }
    my $attribute = $class->{attributes}->{$getterAsCharArray};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getGetterAsCharArrayImplPrintable($className, $objectVariableName);
  }
  foreach my $getter(@{$class->{getters}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $getterComment;
    }
    my $attribute = $class->{attributes}->{$getter};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getGetterImplPrintable($className, $objectVariableName);
  }
  foreach my $getterAsConst(@{$class->{gettersAsConst}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $getterComment;
    }
    my $attribute = $class->{attributes}->{$getterAsConst};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getGetterAsConstImplPrintable($className, $objectVariableName);
  }
  foreach my $getterAsRef(@{$class->{gettersAsRef}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $getterComment;
    }
    my $attribute = $class->{attributes}->{$getterAsRef};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getGetterAsRefImplPrintable($className, $objectVariableName);
  }
  foreach my $getterAsConstRef(@{$class->{gettersAsConstRef}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $getterComment;
    }
    my $attribute = $class->{attributes}->{$getterAsConstRef};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getGetterAsConstRefImplPrintable($className, $objectVariableName);
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  #generate responds to functions
  $isCommented = 0;
  foreach my $respondsTo(@{$class->{respondsTos}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $respondsToComment;
    }
    my $attribute = $class->{attributes}->{$respondsTo};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getRespondsToImplPrintable($className, $objectVariableName);
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  #generate exe functions
  $isCommented = 0;
  foreach my $exe(@{$class->{exes}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $exeComment;
    }
    my $attribute = $class->{attributes}->{$exe};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getExeImplPrintable($className, $objectVariableName, $classProvider);
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  #generate lock functions
  $isCommented = 0;
  foreach my $lock(@{$class->{locks}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $lockComment;
    }
    my $attribute = $class->{attributes}->{$lock};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getLockImplPrintable($className, $objectVariableName);
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getUnlockImplPrintable($className, $objectVariableName);
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  #generate register functions
  $isCommented = 0;
  foreach my $register(@{$class->{registers}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $registerComment;
    }
    my $attribute = $class->{attributes}->{$register};
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getRegisterImplPrintable($className, $objectVariableName, $classProvider);
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getUnregisterImplPrintable($className, $objectVariableName, $classProvider);
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  if($class->isObject() || $class->isDelegate()){
    printf HEADER $functionPrefix;
    printf HEADER "void %s_autorelease(%s * %s){\n", $className, $className, $objectVariableName;
    printf HEADER "\tIA_autorelease(%s);\n", $objectVariableName;
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER "\n";
    printf HEADER $functionPrefix;
    printf HEADER "void %s_release(%s * %s){\n", $className, $className, $objectVariableName;
    printf HEADER "\tIA_release(%s);\n", $objectVariableName;
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER "\n";
  }

  my $superClassName = $class->getSuperClassName();
  my $count = 0;
  while($class->isObject()){
    $count += 1;
    if ($count > 1000){
      die sprintf("Max hierarchy length reached for class %s!", $className);
    }
    if ($superClassName eq "IAObject") {
      last;
    }

    if (not $classProvider->getClass($superClassName)){
      die sprintf("Super class %s in class %s not found!", $superClassName, $className);
    }

    my $superClass = $classProvider->getClass($superClassName);

    #inherit setter functions
    $isCommented = 0;
    foreach my $setterAsCharArray(@{$superClass->{settersAsCharArray}}){
      if($isCommented == 0){
        my $com = $inheritedSetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$setterAsCharArray};
      my $printedHeaderFunction = $attribute->getSetterAsCharArrayPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    foreach my $setter(@{$superClass->{setters}}){
      if($isCommented == 0){
        my $com = $inheritedSetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$setter};
      my $printedHeaderFunction = $attribute->getSetterPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    foreach my $setterAsRef(@{$superClass->{settersAsRef}}){
      if($isCommented == 0){
        my $com = $inheritedSetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$setterAsRef};
      my $printedHeaderFunction = $attribute->getSetterAsRefPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    if($isCommented == 1){
      print HEADER "\n";
    }

    #inherit getter functions
    $isCommented = 0;
    foreach my $getterAsCharArray(@{$superClass->{gettersAsCharArray}}){
      if($isCommented == 0){
        my $com = $inheritedGetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$getterAsCharArray};
      my $printedHeaderFunction = $attribute->getGetterAsCharArrayPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    foreach my $getter(@{$superClass->{getters}}){
      if($isCommented == 0){
        my $com = $inheritedGetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$getter};
      my $printedHeaderFunction = $attribute->getGetterPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    foreach my $getterAsConst(@{$superClass->{gettersAsConst}}){
      if($isCommented == 0){
        my $com = $inheritedGetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$getterAsConst};
      my $printedHeaderFunction = $attribute->getGetterAsConstPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    foreach my $getterAsRef(@{$superClass->{gettersAsRef}}){
      if($isCommented == 0){
        my $com = $inheritedGetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$getterAsRef};
      my $printedHeaderFunction = $attribute->getGetterAsRefPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    foreach my $getterAsConstRef(@{$superClass->{gettersAsConstRef}}){
      if($isCommented == 0){
        my $com = $inheritedGetterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$getterAsConstRef};
      my $printedHeaderFunction = $attribute->getGetterAsConstRefPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    if($isCommented == 1){
      print HEADER "\n";
    }

    #inherit responds to functions
    $isCommented = 0;
    foreach my $respondsTo(@{$superClass->{respondsTos}}){
      if($isCommented == 0){
        my $com = $inheritedRespondsToComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$respondsTo};
      my $printedHeaderFunction = $attribute->getRespondsToPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    if($isCommented == 1){
      print HEADER "\n";
    }

    #inherit exe functions
    $isCommented = 0;
    foreach my $exe(@{$superClass->{exes}}){
      if($isCommented == 0){
        my $com = $inheritedExeComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$exe};
      my $printedHeaderFunction = $attribute->getExePrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }

    if($isCommented == 1){
      print HEADER "\n";
    }

    #inherit lock functions
    $isCommented = 0;
    foreach my $lock(@{$superClass->{locks}}){
      if($isCommented == 0){
        my $com = $inheritedLockComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$lock};
      my $printedHeaderFunction = $attribute->getLockPrintable($superClassName, $objectVariableName);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
      $printedHeaderFunction = $attribute->getUnlockPrintable($superClassName, $objectVariableName);
      ($header, $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }

    if($isCommented == 1){
      print HEADER "\n";
    }

    #inherit register functions
    $isCommented = 0;
    foreach my $register(@{$superClass->{registers}}){
      if($isCommented == 0){
        my $com = $inheritedRegisterComment;
        $com =~ s/\{CLASSNAME\}/$superClassName/g;
        $isCommented = 1;
        print HEADER $com;
      }
      my $attribute = $superClass->{attributes}->{$register};
      my $printedHeaderFunction = $attribute->getRegisterPrintable($superClassName, $objectVariableName, $classProvider);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
      $printedHeaderFunction = $attribute->getUnregisterPrintable($superClassName, $objectVariableName, $classProvider);
      ($header, $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
      print HEADER $functionPrefix . $impl;
    }
    if($isCommented == 1){
      print HEADER "\n";
    }

    #inherit functions
    $isCommented = 0;
    foreach my $function (@{$superClass->{functions}}){
      my $functionName = $function->{name};
      if(not ($function->isSpecialFunction() || $function->isValidFunction($superClassName) == 0)){
        if($isCommented == 0){
          my $com = $inheritedComment;
          $com =~ s/\{CLASSNAME\}/$superClassName/g;
          $isCommented = 1;
          print HEADER $com;
        }
        my $printedHeaderFunction = $function->getHeaderPrintable($superClassName, $objectVariableName);
        (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName);
        printf HEADER $functionPrefix . $impl;
      }
    }
    if($isCommented == 1){
      print HEADER "\n";
    }

    if ($superClass->getSuperClassName() eq "") {
      die sprintf("Invalid class hierarchy of \"%s\": Cannot extend \"%s\" because it is not a class.", $className, $superClassName)
    }

    $superClassName = $superClass->getSuperClassName();
  }

  $superClassName = $class->getSuperClassName();
  if($superClassName ne ""){
    print HEADER $doxygenExtendComment;
    print HEADER "/**\n";
    print HEADER " * \@class $className\n";
    print HEADER " * \@extends $superClassName\n";
    print HEADER " */\n\n\n";
  }

  $isCommented = 0;
  foreach my $function (@{$class->{functions}}){
    if($isCommented == 0){
      $isCommented = 1;
      print HEADER $doxygenLinkComment;
    }
    if($function->isDeinitFunction()){
      print HEADER $function->getDoxygenComment($className, $destructorMacro);
    }
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  close HEADER;

  #generate event class
  if($class->isEvent()){
    my $eventClassName = getEventNameForClassName($className);
    my $listName = "delegates";
    my $eventFileName = $eventClassName . ".h";
    my $eventPath = $genDir . "/" . $eventFileName;

    my @executeableFunctions = ();
    $class->addExeFunctionsToList($objectVariableName, \@executeableFunctions);

    $superClassName = $class->getSuperClassName();
    while($classProvider->getClass($superClassName)){
      my $superClass = $classProvider->getClass($superClassName);
      $superClass->addExeFunctionsToList($objectVariableName, \@executeableFunctions, $eventClassName);
      $superClassName = $superClass->getSuperClassName();
    }

    open HEADER, ">", $eventPath or die "unable to open header file $eventPath for writing!";
    print HEADER $copyright;
    print HEADER "\n";
    print HEADER "#ifndef ${eventClassName}_h\n";
    print HEADER "#define ${eventClassName}_h\n";
    print HEADER "\n";
    print HEADER "#include \"IAStructArrayList.h\"\n";
    print HEADER "#include \"IALibrary.h\"\n";
    print HEADER "#include \"$className.h\"\n";
    print HEADER "\n";
    print HEADER "typedef struct{\n";
    print HEADER "\tIAStructArrayList * $listName;\n";
    print HEADER "} $eventClassName;\n";
    print HEADER "\n";
    printf HEADER $memberOfFormat, $eventClassName;
    print HEADER $functionPrefix . " $constructorMacro void ${eventClassName}_init($eventClassName * this){\n";
    print HEADER "\tIA_STRUCT_ARRAY_LIST_VOID_MALLOC_MAKE_WITH_CLASSNAME(this->$listName, 8, \"${eventClassName}\");\n";
    printf HEADER "\tIA_incrementInitCountForClass(\"%s\");\n", $eventClassName;
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER $functionPrefix . " $destructorMacro void ${eventClassName}_deinit($eventClassName * this);\n";
    print HEADER $functionPrefix . "$eventClassName * ${eventClassName}_new(){\n";
    print HEADER "\t${eventClassName} * this = IA_newWithClassName(sizeof(${eventClassName}), (void (*)(void *)) ${eventClassName}_deinit, \"${eventClassName}\");\n";
    print HEADER "\t${eventClassName}_init(this);\n";
    print HEADER "\treturn this;\n";
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER $functionPrefix . "$eventClassName * ${eventClassName}_with(){\n";
    print HEADER "\t${eventClassName} * this = ${eventClassName}_new();\n";
    print HEADER "\tIA_autorelease(this);\n";
    print HEADER "\treturn this;\n";
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER $functionPrefix . "void ${eventClassName}_retain($eventClassName * this){\n";
    print HEADER "\tIA_retain(this);\n";
    print HEADER "}\n";
    print HEADER "\n";
    printf HEADER $memberOfFormat, $eventClassName;
    print HEADER $functionPrefix . "void ${eventClassName}_register($eventClassName * this, $className * delegate){\n";
    if ($class->{isEvent}) {
      print HEADER "\tIA_retain(delegate);\n";
    }
    print HEADER "\tIA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(this->$listName, \"${eventClassName}\");\n";
    print HEADER "\tIAStructArrayList_add(this->$listName, delegate);\n";
    print HEADER "}\n";
    print HEADER "\n";
    printf HEADER $memberOfFormat, $eventClassName;
    print HEADER $functionPrefix . "void ${eventClassName}_unregister($eventClassName * this, $className * delegate){\n";
    print HEADER "\tdebugOnly(bool isFound = false;)\n";
    print HEADER "\tfor (size_t i = 0; i < IAStructArrayList_getCurrentSize(this->$listName); i++) {\n";
    print HEADER "\t\t$className * delegateInList = ($className *) IAStructArrayList_get(this->$listName, i);\n";
    print HEADER "\t\tif (delegateInList == delegate) {\n";
    print HEADER "\t\t\tIAStructArrayList_removeAtIndex(this->$listName, i);\n";
    if ($class->{isEvent}) {
      print HEADER "\t\t\tIA_release(delegateInList);\n";
    }
    print HEADER "\t\t\tdebugOnly(isFound = true);\n";
    print HEADER "\t\t\tbreak;\n";
    print HEADER "\t\t}\n";
    print HEADER "\t}\n";
    print HEADER "\tdebugAssert(isFound == true && \"Delegate was not found!\");\n";
    print HEADER "}\n";
    print HEADER "\n";
    foreach my $function (@executeableFunctions){
      if($function->isVoidFunction() == 1){
        printf HEADER $memberOfFormat, $eventClassName;
        print HEADER $functionPrefix . $function->getExeEventImplementationPrintable($eventClassName, $className, $listName, "this");
      }
    }
    printf HEADER $memberOfFormat, $eventClassName;
    print HEADER $functionPrefix . " $destructorMacro void ${eventClassName}_deinit($eventClassName * this){\n";
    print HEADER "\tIA_STRUCT_ARRAY_LIST_VOID_FREE_WITH_CLASSNAME(this->$listName, \"${eventClassName}\");\n";
    print HEADER "\tIA_decrementInitCountForClass(\"${eventClassName}\");\n";
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER $functionPrefix . "void ${eventClassName}_autorelease($eventClassName * this){\n";
    print HEADER "\tIA_autorelease(this);\n";
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER $functionPrefix . "void ${eventClassName}_release($eventClassName * this){\n";
    print HEADER "\tIA_release(this);\n";
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER "\n";
    print HEADER "#endif\n";
    print HEADER "\n";
    close HEADER;
  }
}

1;
