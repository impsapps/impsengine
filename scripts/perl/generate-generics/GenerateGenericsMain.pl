#!/usr/bin/perl

use strict;
use warnings;

BEGIN {push @INC, '.'}

my $usage =
"usage: ./GenerateGenericsMain.pl {moduleGroup} {moduleName} {sourceDir} [additionalIncludeDir, ...]\n" .
"moduleGroup ... the group of the module\n" .
"moduleName ... the module name\n" .
"sourceDir ... path to your source\n" .
"additionalIncludeDir ... dir to include recursively\n";


my $genericsFolderName = "generics";
my $genericsHeaderFolderName = "headers";
my $genericsClassExtension = "Generated";

my $copyright = "//  \n" .
"//  This file has been automatically generated.\n" .
"//  \n" .
"//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.\n" .
"//  \n";

my $constructorComment = "// Constructor methods:\n";
my $constructorDoxygenLinkComment = "// Link constructor functions for doxygen:\n";
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

package Main;

BEGIN {
  use Cwd 'abs_path';
  my $absPath = abs_path($0);
  $absPath =~ s/\/[^\/]*$//;
  push @INC, $absPath
}

use Class;
use Attribute;
use Expressions;
use Function;
use Helper;
use Parsing;
use Constants;

if (scalar @ARGV < 3){
  die "Invalid number of arguments!\n" . "Arguments submitted: @ARGV\n" . $usage;
}


my $moduleGroup = $ARGV[0];
my $moduleName = $ARGV[1];
$moduleName =~ s/\+/_/;
my $sourceDir = $ARGV[2];
my $genericsDir = $sourceDir . "/" . $genericsFolderName;

if (-d $sourceDir){
  if (not -d $genericsDir){
    mkdir $genericsDir;
  }
  if (not -d $genericsDir . "/" . $genericsHeaderFolderName){
    mkdir $genericsDir . "/" . $genericsHeaderFolderName;
  }
}


my @includeDirs;

my $currentPosition = 3;
while ($currentPosition < scalar @ARGV){
  push(@includeDirs, $ARGV[$currentPosition]);
  $currentPosition++;
}


my %classes;
my %sourceClasses;

addClasses($sourceDir, \%classes);
foreach my $key (keys %classes){
  $sourceClasses{$key} = $classes{$key};
}

foreach my $includeDir (@includeDirs){
  addClasses($includeDir, \%classes);
}

opendir(HEADERFILESDIR, $genericsDir . "/". $genericsHeaderFolderName);
my @availableHeaderFiles = readdir(HEADERFILESDIR);
my %filesToDelete = ();
foreach my $name (@availableHeaderFiles){
  if (not $name =~ m/^\./){
    $filesToDelete{$name} = "";
  }
}
closedir(HEADERFILESDIR);

foreach my $key (sort keys %sourceClasses){
  my $class = $sourceClasses{$key};
  my $className = $class->{className};
  my $fileName = $className . '+' . $genericsClassExtension . ".h";
  my $path = $genericsDir . "/" . $genericsHeaderFolderName . "/" . $fileName;

  my $objectVariableName = $class->getObjectVariableName();

  if($class->isValidClass() == 0){
    next;
  }

  if(exists($filesToDelete{$fileName})){
    delete($filesToDelete{$fileName});
  }

  open HEADER, ">", $path or die "unable to open header file $path for writing!";
  print HEADER $copyright;
  print HEADER "\n\n";

  print HEADER "#include \"IALibrary.h\"\n";
  print HEADER "#include \"IAAutoreleasePool.h\"\n\n\n";

  #generate new functions
  my $isCommented = 0;

  if ($class->{isObject}) {
    foreach my $function (@{$class->{functions}}){
      my $isInitFunction = $function->isInitFunction();
      my $isMakeFunction = $function->isMakeFunction();
      if(($isInitFunction || $isMakeFunction) && $function->isValidFunction($className) == 1){
        if($isMakeFunction){
          if($class->{hasInitFunction} == 1){
            next;
          }
        }else{
          die "Error: isInitFunction == 0" if($isInitFunction == 0);
          die "Error: class->{hasInitFunction} != 1" if($class->{hasInitFunction} != 1);
        }
        if($isCommented == 0){
          print HEADER $constructorComment;
        }
        $isCommented = 1;

        my $functionNameForNew = $function->{name};
        $functionNameForNew =~ s/^(init|make)/new/;
        my $functionNameForWith = $function->{name};
        $functionNameForWith =~ s/^(init|make)//;
        if ($functionNameForWith eq "") {
          $functionNameForWith = "with";
        }else{
          $functionNameForWith = lcfirst($functionNameForWith);
        }

        my $definitionForNew = $className . " * " . $className . "_" . $functionNameForNew;
        my $definitionForWith = $className . " * " . $className . "_" . $functionNameForWith;

        my $params = $function->{params};
        $params = removeFirstParamFromParams($params);
        $params = normalizeParams($params);
        my $valueParams = convertParamsToValues($params);

        my $deinitFunction = "NULL";
        if ($isInitFunction){
          $deinitFunction = "(void (*)(void *)) " . $className . "_deinit";
        }

        printf HEADER $memberOfFormat, $className;
        printf HEADER $constructorPrefix . $functionPrefix;
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
        print HEADER "\tIAAutoreleasePool_add(this);\n";
        print HEADER "\treturn this;\n";
        print HEADER "}\n\n";
      }
    }
  }

  if ($class->{isObject} || $class->{isDelegate}) {
    printf HEADER $functionPrefix;
    printf HEADER "void %s_retain($className * this){\n", $className, $className;
    printf HEADER "\tIA_retain(this);\n";
    print HEADER "}\n\n";
  }

  if($isCommented){
    print HEADER "\n";
  }

  $isCommented = 0;
  foreach my $function (@{$class->{functions}}){
    if($function->isConstructorFunction()){
      if($isCommented == 0){
        $isCommented = 1;
        print HEADER $constructorDoxygenLinkComment;
      }
      print HEADER $function->getDoxygenComment($className);
    }
  }
  if($isCommented){
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
    print HEADER $functionPrefix . $attribute->getExeImplPrintable($className, $objectVariableName, \%classes);
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
    print HEADER $functionPrefix . $attribute->getRegisterImplPrintable($className, $objectVariableName, \%classes);
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . $attribute->getUnregisterImplPrintable($className, $objectVariableName, \%classes);
  }
  if($isCommented == 1){
    print HEADER "\n";
  }

  $isCommented = 0;
  foreach my $function (@{$class->{functions}}){
    if(not $function->isSpecialFunction()){
      if($isCommented == 0){
        $isCommented = 1;
        print HEADER $doxygenLinkComment;
      }
      print HEADER $function->getDoxygenComment($className);
    }
  }
  if($isCommented == 1){
    print HEADER "\n";
  }


  if($class->{isObject} || $class->{isDelegate}){
    printf HEADER $functionPrefix;
    printf HEADER "void %s_release(%s * %s){\n", $className, $className, $objectVariableName;
    printf HEADER "\tIA_release(%s);\n", $objectVariableName;
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER "\n";
  }

  my $superClassName = $class->getSuperClassName();
  my $count = 0;
  while($class->{isObject}){
    $count += 1;
    if ($count > 1000){
      die sprintf("Max view hierarchy length reached for class %s!", $className);
    }
    if ($superClassName eq "IAObject") {
      last;
    }

    if (not exists ($classes{$superClassName})){
      die sprintf("Super class %s in class %s not found!", $superClassName, $className);
    }

    my $superClass = $classes{$superClassName};

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
      my $printedHeaderFunction = $attribute->getRegisterPrintable($superClassName, $objectVariableName, \%classes);
      (my $header, my $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName, \%classes);
      print HEADER $functionPrefix . $impl;
      $printedHeaderFunction = $attribute->getUnregisterPrintable($superClassName, $objectVariableName, \%classes);
      ($header, $impl) = inheritFunction($printedHeaderFunction, $className, $objectVariableName, \%classes);
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
    print HEADER " * \@struct $className\n";
    print HEADER " * \@extends $superClassName\n";
    print HEADER " */\n\n\n";
  }

  close HEADER;

  #generate event class
  if($class->{isEvent} == 1){
    my $eventClassName = $className;
    $eventClassName =~ s/(Delegate)?$/Event/;
    my $listName = "delegates";
    my $eventFileName = $eventClassName . ".h";
    my $eventPath = $genericsDir . "/" . $genericsHeaderFolderName . "/" . $eventFileName;

    if(exists($filesToDelete{$eventFileName})){
      delete($filesToDelete{$eventFileName});
    }

    my @executeableFunctions = ();
    $class->addExeFunctionsToList($objectVariableName, \@executeableFunctions);

    $superClassName = $class->getSuperClassName();
    while(exists ($classes{$superClassName})){
      my $superClass = $classes{$superClassName};
      $superClass->addExeFunctionsToList($objectVariableName, \@executeableFunctions, $eventClassName);
      $superClassName = $superClass->getSuperClassName();
    }

    open HEADER, ">", $eventPath or die "unable to open header file $eventPath for writing!";
    print HEADER $copyright;
    print HEADER "\n";
    print HEADER "#ifndef ${eventClassName}_h\n";
    print HEADER "#define ${eventClassName}_h\n";
    print HEADER "\n";
    print HEADER "#include \"IAArrayList.h\"\n";
    print HEADER "#include \"IAArrayListIterator.h\"\n";
    print HEADER "#include \"IALibrary.h\"\n";
    print HEADER "#include \"$className.h\"\n";
    print HEADER "\n";
    print HEADER "typedef struct{\n";
    print HEADER "\tIAArrayList $listName;\n";
    print HEADER "} $eventClassName;\n";
    print HEADER "\n";
    print HEADER $constructorPrefix . $functionPrefix . "void ${eventClassName}_init($eventClassName * this){\n";
    print HEADER "\tIAArrayList_init(&this->$listName, 8);\n";
    printf HEADER "\tIA_incrementInitCountForClass(\"%s\");\n", $eventClassName;
    print HEADER "}\n";
    print HEADER "\n";
    print HEADER $functionPrefix . "void ${eventClassName}_deinit($eventClassName * this);\n";
    print HEADER $constructorPrefix . $functionPrefix . "$eventClassName * ${eventClassName}_new(){\n";
    print HEADER "\t${eventClassName} * this = IA_newWithClassName(sizeof(${eventClassName}), (void (*)(void *)) ${eventClassName}_deinit, \"${eventClassName}\");\n";
    print HEADER "\t${eventClassName}_init(this);\n";
    print HEADER "\treturn this;\n";
    print HEADER "}\n";
    print HEADER "\n";
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . "void ${eventClassName}_retain($eventClassName * this){\n";
    print HEADER "\tIA_retain(this);\n";
    print HEADER "}\n";
    print HEADER "\n";
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . "void ${eventClassName}_register($eventClassName * this, $className * delegate){\n";
    print HEADER "\tIAArrayList_add(&this->$listName, delegate);\n";
    print HEADER "}\n";
    print HEADER "\n";
    printf HEADER $memberOfFormat, $className;
    print HEADER $functionPrefix . "$className * ${eventClassName}_unregister($eventClassName * this, $className * delegate){\n";
    print HEADER "\treturn IAArrayList_removeObject(&this->$listName, delegate);\n";
    print HEADER "}\n";
    print HEADER "\n";
    foreach my $function (@executeableFunctions){
      if($function->isVoidFunction() == 1){
        printf HEADER $memberOfFormat, $className;
        print HEADER $functionPrefix . $function->getExeEventImplementationPrintable($eventClassName, $className, $listName, "this");
      }
    }
    print HEADER $functionPrefix . "void ${eventClassName}_deinit($eventClassName * this){\n";
    print HEADER "\tIAArrayList_deinit(&this->$listName);\n";
    print HEADER "\tIA_decrementInitCountForClass(\"${eventClassName}\");\n";
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

foreach my $key (keys %filesToDelete) {
  my $file = $genericsDir . "/" . $genericsHeaderFolderName . "/" . $key;
  unlink $file  or die sprintf("Could not unlink $file: $!\n");
}

my $moduleGenericsPath = $genericsDir . "/" . $genericsHeaderFolderName . "/" . $moduleName . '+' . $genericsClassExtension . ".h";
open HEADER, ">", $moduleGenericsPath or die "unable to open header file $moduleGenericsPath for writing!";

print HEADER "/**\n";
print HEADER " * \\addtogroup $moduleGroup\n";
print HEADER " */\n\n";


print HEADER "/**\n";
print HEADER " * \\addtogroup $moduleName\n";
print HEADER " * \\ingroup $moduleGroup\n";
print HEADER " * \@{\n";
print HEADER " */\n";

foreach my $key (sort keys %sourceClasses){
  my $class = $sourceClasses{$key};
  if($class->isValidClass()){
    my $className = $class->{className};
    print HEADER "/// \\class $className\n";
  }
}

my $headerFiles = getHeaderFilesForDir($sourceDir);
foreach my $value (@$headerFiles){
  print HEADER "/// \\file $value\n";
}

print HEADER "/**\n";
print HEADER " * \@}\n";
print HEADER " */\n\n";
close HEADER;
