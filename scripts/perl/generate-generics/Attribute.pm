#!/usr/bin/perl

use strict;
use warnings;

package Attribute;

require Exporter;
our @ISA = qw(Exporter);

use Expressions;
use Helper;

sub newWithCommand{
	my $class = shift;
	my $command = shift;
	my $self;
	if($command =~ m/^\s*$matchFunction\s*;\s*$/){
		$self = {
			name => $2,
			type => $1,
			params => $3,
			isFunctionPointer => 1
		}
	}elsif($command =~ m/^\s*$matchType\s*$matchNameAndExtension\s*;\s*$/){
		$self = {
			name => $2,
			type => $1,
			params => $3 ? $3 : "",
			isFunctionPointer => 0
		}
	}else{
		return;
	}
	bless $self, $class;
	return $self;
}

sub isObjectPointer{
	my $self = shift;
	if ($self->{isFunctionPointer}) {
		return 0;
	}
	if ($self->{type} =~ m/\*$/) {
		return 1;
	}else{
		return 0;
	}
}

sub privateGetSetterFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	if($self->{isFunctionPointer} == 0){
		return sprintf "void %s_set%s(%s * %s, %s %s)", $className, ucfirst($self->{name}), $className, $variableName, $self->{type}, $self->{name};
	}else{
		return sprintf "void %s_set%sFunction(%s * %s, %s(*%s)(%s))", $className, ucfirst($self->{name}), $className, $variableName, $self->{type}, $self->{name}, $self->{params};
	}
}

sub getSetterPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetSetterFunction($className, $variableName) . ";\n";
}

sub getSetterImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $setter = $self->privateGetSetterFunction($className, $variableName) . "{\n";
	$setter = $setter . "\t$variableName" . "->" . $self->{name} . " = " . $self->{name} . ";\n}\n\n";
	return $setter;
}

sub privateGetReferenceOfTyp{
	my $self = shift;
	if($self->{type} =~ m/\*$/){
		return $self->{type} . "*";
	}else{
		return $self->{type} . " *";
	}
}

sub privateGetSetterAsRefFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	if($self->{isFunctionPointer} == 0){
		return sprintf "void %s_set%s(%s * %s, %s %s)", $className, ucfirst($self->{name}), $className, $variableName, $self->privateGetReferenceOfTyp(), $self->{name};
	}else{
		die sprintf "setAsRef: function pointers are not implemented for attribute \"%s\" of type \"%s\" in class \"%s\"!", $self->{name}, $self->{type}, $className;
	}
}

sub getSetterAsRefPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetSetterAsRefFunction($className, $variableName) . ";\n";
}

sub getSetterAsRefImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $setter = $self->privateGetSetterAsRefFunction($className, $variableName) . "{\n";
	$setter = $setter . "\t$variableName" . "->" . $self->{name} . " = *" . $self->{name} . ";\n}\n\n";
	return $setter;
}

sub privateGetSetterAsCharArrayFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return sprintf "void %s_set%s(%s * %s, const char * %s)", $className, ucfirst($self->{name}), $className, $variableName, $self->{name};
}

sub getSetterAsCharArrayPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetSetterAsCharArrayFunction($className, $variableName) . ";\n";
}

sub getSetterAsCharArrayImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $setCharArrayCall = "";
	if($self->{type} =~ m/^IAString\s*\*$/){
		$setCharArrayCall = sprintf "IAString_set(%s->%s, %s)", $variableName, $self->{name}, $self->{name};
	}elsif($self->{type} =~ m/^IAString$/){
		$setCharArrayCall = sprintf "IAString_set(&%s->%s, %s)", $variableName, $self->{name}, $self->{name};
	}else{
		die sprintf "Cannot generate setAsCharArray for attribute \"%s\" of type \"%s\" in class \"%s\"! Only working if attribute is of type \"IAString *\" or \"IAString\".", $self->{name}, $self->{type}, $className;
	}
	return  $self->privateGetSetterAsCharArrayFunction($className, $variableName) . "{\n" . "\t" . $setCharArrayCall . ";\n}\n\n";
}

sub privateGetGetterFunctionName{
	my $self = shift;

	if($self->{isFunctionPointer} == 0){
		if($self->{name} =~ m/^(is|are|was|were|has|have|had|can|could|should|shall|may)[A-Z]/){
			return $self->{name};
		}else{
			return sprintf "get%s", ucfirst($self->{name});
		}
	}else{
		return sprintf "get%sFunction", ucfirst($self->{name});
	}
}

sub privateGetGetterFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $functionName = $self->privateGetGetterFunctionName();

	if($self->{isFunctionPointer} == 0){
		return sprintf "%s %s_%s(const %s * %s)", $self->{type}, $className, $functionName, $className, $variableName;
	}else{
		return sprintf "%s (* %s_%s(const %s * %s))(%s)", $self->{type}, $className, $functionName, $className, $variableName, $self->{params};
	}
}

sub getGetterPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetGetterFunction($className, $variableName) . ";\n";
}

sub getGetterImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return  $self->privateGetGetterFunction($className, $variableName) . "{\n" . "\treturn $variableName" . "->" . $self->{name} . ";\n}\n\n";
}

sub getGetterAsConstPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return "const " . $self->privateGetGetterFunction($className, $variableName) . ";\n";
}

sub getGetterAsConstImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return "const " . $self->privateGetGetterFunction($className, $variableName) . "{\n" . "\treturn $variableName" . "->" . $self->{name} . ";\n}\n\n";
}

sub privateGetGetterAsRefFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classNamePrefix = shift // "";
	my $functionName = $self->privateGetGetterFunctionName();

	if($self->{isFunctionPointer} == 0){
		return sprintf "%s %s_%s(%s%s * %s)", $self->privateGetReferenceOfTyp(), $className, $functionName, $classNamePrefix, $className, $variableName;
	}else{
		die sprintf "getAsRef: function pointers are not implemented for attribute \"%s\" of type \"%s\" in class \"%s\"!", $self->{name}, $self->{type}, $className;
	}
}

sub getGetterAsRefPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetGetterAsRefFunction($className, $variableName) . ";\n";
}

sub getGetterAsRefImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $dereferenceString = "&";
	if($self->{params} ne ""){
		$dereferenceString = "";
	}
	return  $self->privateGetGetterAsRefFunction($className, $variableName) . "{\n" . "\treturn $dereferenceString$variableName" . "->" . $self->{name} . ";\n}\n\n";
}

sub getGetterAsConstRefPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return "const " . $self->privateGetGetterAsRefFunction($className, $variableName, "const ") . ";\n";
}

sub getGetterAsConstRefImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $dereferenceString = "&";
	if($self->{params} ne ""){
		$dereferenceString = "";
	}
	return "const " . $self->privateGetGetterAsRefFunction($className, $variableName, "const ") . "{\n" . "\treturn $dereferenceString$variableName" . "->" . $self->{name} . ";\n}\n\n";
}

sub privateGetGetterAsCharArrayFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return sprintf "const char * %s_get%s(const %s * %s)", $className, ucfirst($self->{name}), $className, $variableName;
}

sub getGetterAsCharArrayPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetGetterAsCharArrayFunction($className, $variableName) . ";\n";
}

sub getGetterAsCharArrayImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $toCharArrayCall = "";
	if($self->{type} =~ m/^IAString\s*\*$/){
		$toCharArrayCall = sprintf "IAString_toCharArray(%s->%s)", $variableName, $self->{name};
	}elsif($self->{type} =~ m/^IAString$/){
		$toCharArrayCall = sprintf "IAString_toCharArray(&%s->%s)", $variableName, $self->{name};
	}else{
		die sprintf "Cannot generate getAsCharArray for attribute \"%s\" of type \"%s\" in class \"%s\"! Only working if attribute is of type \"IAString *\" or \"IAString\".", $self->{name}, $self->{type}, $className;
	}
	return  $self->privateGetGetterAsCharArrayFunction($className, $variableName) . "{\n" . "\treturn " . $toCharArrayCall . ";\n}\n\n";
}

sub privateGetRespondsToFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	if($self->{isFunctionPointer} == 0){
		die "privatGetRespondsToFunction called with non function attribute!";
	}else{
		return sprintf "bool %s_respondsTo%s(%s * %s)", $className, ucfirst($self->{name}), $className, $variableName;
	}
}

sub getRespondsToPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetRespondsToFunction($className, $variableName) . ";\n";
}

sub getRespondsToImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetRespondsToFunction($className, $variableName) . "{\n" . "\tif (${variableName}->$self->{name} != NULL){\n\t\treturn true;\n\t}else{\n\t\treturn false;\n\t}\n}\n\n";
}

sub isValidExeFunction{
	my $self = shift;
	if($self->{params} =~ m/^\s*[\w][\w\d]+\s*\*\s*$matchName\s*(,\s*|$)/){
		return 1;
	}else{
		return 0;
	}
}

sub privateGetParamsForExeFunction{
	my $self = shift;
	my $params = $self->{params};
	$params =~ s/^[^,]*(,\s*|$)//;
	return $params;
}

sub privateGetExeHeaderFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $params = $self->privateGetParamsForExeFunction();
	if($params eq ""){
		return sprintf "%s %s_%s(const %s * %s)", $self->{type}, $className, $self->{name}, $className, $variableName;
	}else{
		return sprintf "%s %s_%s(const %s * %s, %s)", $self->{type}, $className, $self->{name}, $className, $variableName, $params;
	}
}

sub privateGetExeImplementationFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $params = shift;
	if($params eq ""){
		return sprintf "%s %s_%s(const %s * %s)", $self->{type}, $className, $self->{name}, $className, $variableName;
	}else{
		return sprintf "%s %s_%s(const %s * %s, %s)", $self->{type}, $className, $self->{name}, $className, $variableName, $params;
	}
}

sub getExePrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetExeHeaderFunction($className, $variableName) . ";\n";
}

sub getExeImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classProvider = shift;

	$self->{params} =~ m/^\s*$matchType\s*$matchName/;
	my $correspondingObjectVariableName = $2;
	my $correspondingObjectTemp = $correspondingObjectVariableName;
	my $classTemp = $classProvider->getClass($className);
	while(not exists ($classTemp->{attributes}->{$correspondingObjectVariableName})){
		my $superClassName = $classTemp->getSuperClassName();
		if ($classProvider->getClass($superClassName)){
			$correspondingObjectTemp = $classTemp->{superClassName} . "." . $correspondingObjectTemp;
			$classTemp = $classProvider->getClass($superClassName);
		}else{
			$correspondingObjectTemp = $correspondingObjectVariableName;
			last;
		}
	}

	my $correspondingObject = $variableName . "->" . $correspondingObjectTemp;
	my $params = $self->privateGetParamsForExeFunction();
	$params = normalizeParams($params);
	my $implementationFunction = $self->privateGetExeImplementationFunction($className, $variableName, $params);
	$params = convertParamsToValues($params);
	if($params && (not $params eq "")){
		$params = $correspondingObject . ", " . $params;
	}else{
		$params = $correspondingObject;
	}
	if($self->{type} eq "void"){
		return sprintf "%s{\n\tif (%s->%s != NULL){\n\t\t%s->%s(%s);\n\t\}\n}\n\n", $implementationFunction, $variableName, $self->{name}, $variableName, $self->{name}, $params;
	}else{
		return sprintf "%s{\n\treturn %s->%s(%s);\n}\n\n", $implementationFunction, $variableName, $self->{name}, $params;
	}
}

sub privateGetLockFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return sprintf "void %s_lock(const %s * %s)", $className, $className, $variableName;
}

sub privateGetUnlockFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return sprintf "void %s_unlock(const %s * %s)", $className, $className, $variableName;
}

sub getLockPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetLockFunction($className, $variableName) . ";\n";
}

sub getUnlockPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	return $self->privateGetUnlockFunction($className, $variableName) . ";\n";
}

sub getLockImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $lockImpl = $self->privateGetLockFunction($className, $variableName) . "{\n";
	$lockImpl = $lockImpl . "\tIALock_lock(" . "$variableName" . "->" . $self->{name} . ");\n}\n\n";
	return $lockImpl;
}

sub getUnlockImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;

	my $lockImpl = $self->privateGetUnlockFunction($className, $variableName) . "{\n";
	$lockImpl = $lockImpl . "\tIALock_unlock(" . "$variableName" . "->" . $self->{name} . ");\n}\n\n";
	return $lockImpl;
}

sub privateGetDelegateName(){
	my $self = shift;
	my $className = shift;
	my $classProvider = shift;
	if(!($self->{type} =~ m/Event(\s*\*)?$/)){
		die "Cannot generate register functions for event \"" . $self->{name} . "\" in class \"$className\" because the it is not an event!\n";
	}

	my $delegateName1 = $self->{type};
	$delegateName1 =~ s/Event(\s*\*)?$/Delegate/;
	my $delegateName2 = $self->{type};
	$delegateName2 =~ s/Event(\s*\*)?$//;
	if($classProvider->getClass($delegateName1)){
		return $delegateName1;
	}elsif($classProvider->getClass($delegateName2)){
		return $delegateName2;
	}else{
		die "Cannot generate register functions for event \"" . $self->{name} . "\" in class \"$className\" because such an event cannot be found!\n";
	}
}

sub privateGetRegisterFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classProvider = shift;
	my $delegateName = $self->privateGetDelegateName($className, $classProvider);
	my $delegateVariableName = "delegate";
	return sprintf "void %s_registerFor%s(%s * %s, %s * %s)", $className, ucfirst($self->{name}), $className, $variableName, $delegateName, $delegateVariableName;
}

sub privateGetUnregisterFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classProvider = shift;
	my $delegateName = $self->privateGetDelegateName($className, $classProvider);
	my $delegateVariableName = "delegate";
	return sprintf "void %s_unregisterFrom%s(%s * %s, %s * %s)", $className, ucfirst($self->{name}), $className, $variableName, $delegateName, $delegateVariableName;
}

sub getRegisterPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classProvider = shift;
	return $self->privateGetRegisterFunction($className, $variableName, $classProvider) . ";\n";
}

sub getUnregisterPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classProvider = shift;
	return $self->privateGetUnregisterFunction($className, $variableName, $classProvider) . ";\n";
}

sub privateGetOptionalEnreferenceSymbolForRegisterFunctions{
	my $self = shift;
	if(index($self->{type}, "*") == -1){
		return "&";
	}else{
		return "";
	}
}

sub getRegisterImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classProvider = shift;
	my $delegateName = $self->privateGetDelegateName($className, $classProvider);
	my $delegateVariableName = "delegate";
	my $registerImpl = $self->privateGetRegisterFunction($className, $variableName, $classProvider) . "{\n";
	my $type = $self->{type};
	$type =~ s/^([\w\d]*).*$/$1/;
	my $optionalEnreferenceSymbol = $self->privateGetOptionalEnreferenceSymbolForRegisterFunctions();
	$registerImpl = $registerImpl . sprintf ("\t%s_register(%s%s->%s, %s)", $type, $optionalEnreferenceSymbol, $variableName, $self->{name}, $delegateVariableName) . ";\n}\n\n";
	return $registerImpl;
}

sub getUnregisterImplPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $classProvider = shift;
	my $delegateName = $self->privateGetDelegateName($className, $classProvider);
	my $delegateVariableName = "delegate";
	my $unregisterImpl = $self->privateGetUnregisterFunction($className, $variableName, $classProvider) . "{\n";
	my $type = $self->{type};
	$type =~ s/^([\w\d]*).*$/$1/;
	my $optionalEnreferenceSymbol = $self->privateGetOptionalEnreferenceSymbolForRegisterFunctions();
	$unregisterImpl = $unregisterImpl . sprintf ("\t%s_unregister(%s%s->%s, %s)", $type, $optionalEnreferenceSymbol, $variableName, $self->{name}, $delegateVariableName) . ";\n}\n\n";
	return $unregisterImpl;
}

1;
