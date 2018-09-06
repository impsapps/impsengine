#!/usr/bin/perl

use strict;
use warnings;

package Function;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(convertFunctionNameForNew convertFunctionNameForWith);

use Expressions;
use Helper;
use Constants;


sub convertFunctionNameForNew{
	my $functionName = shift;
	$functionName =~ s/^(init|make)/new/;
	return $functionName;
}

sub convertFunctionNameForWith{
	my $functionName = shift;
	$functionName =~ s/^(init|make)//;
	if ($functionName eq "") {
		$functionName = "with";
	}else{
		$functionName = lcfirst($functionName);
	}
	return $functionName;
}

sub new{
	my $class = shift;
	my $self = {
		name => shift // "",
		returnType => shift // "",
		params => shift // "",
		comment => shift // ""
	};
	bless $self, $class;
	return $self;
}

sub initWithHeader{
	my $self = shift;
	my $className = shift;
	my $header = shift;
	my $comment = shift;
	my $returnCode = 0;

	if ($header =~ m/($matchType|$matchFunction)\s*$matchName\s*\($matchParams\)\s*(;|\{)/){
		my $returnType = $1;
		my $params = $7;
		my $functionName = $6;
		#This if clause is needed because otherwise returns on statements in inline functions will be detected as functions.
		#Please note, that inline functions are not officially supported yet.
		#It is to prevent of throwing "invalid function name" errors because of generated inline function in event classes.
		if($returnType ne "return" and $returnType ne "define"){
			if($functionName =~ m/${className}_$matchName/){
				$functionName = $1;
				$returnCode = 1;
				if ($functionName =~ m/^deinit.+/){
					$returnCode = 3;
				}
			}else{
				$returnCode = 2;
			}
		}

		$self->{name} = $functionName;
		$self->{returnType} = $returnType;
		$self->{params} = $params;
		$self->{comment} = $comment;
		return $returnCode;
	}else{
		return 0;
	}
}

sub isValidFunction{
	my $self = shift;
	my $className = shift;
	if(!($self->isStaticFunction($className)) && !($self->{params} =~ m/\.\.\./)){
		return 1;
	}else{
		return 0;
	}
}

sub isStaticFunction{
	my $self = shift;
	my $className = shift;
	my $params = $self->{params};
	if($params =~ m/^(\s*const)?\s*$className\s*\*\s*($matchName|)\s*(,|$)/){
		return 0;
	}else{
		return 1;
	}
}

sub isFirstArgumentConst{
	my $params = shift;
	if($params =~ m/^\s*const/){
		return 1;
	}else{
		return 0;
	}
}

sub isInitFunction{
	my $self = shift;
	if(index($self->{name}, 'init') == 0){
		return 1;
	}else{
		return 0;
	}
}

sub isMakeFunction{
	my $self = shift;
	if(index($self->{name}, 'make') == 0){
		return 1;
	}else{
		return 0;
	}
}

sub isDeinitFunction{
	my $self = shift;
	if(index($self->{name}, 'deinit') == 0){
		return 1;
	}else{
		return 0;
	}
}

sub isNewFunction{
	my $self = shift;
	if(index($self->{name}, 'new') == 0){
		return 1;
	}else{
		return 0;
	}
}

sub isSpecialFunction{
	my $self = shift;
	if($self->isInitFunction()
			|| $self->isMakeFunction()
			|| $self->isDeinitFunction()
			|| $self->isNewFunction()){
		return 1;
	}else{
		return 0;
	}
}

sub getComment{
	my $self = shift;
	return $self->{comment};
}

sub getPureFunction{
	my $self = shift;
	my $className = shift . "_" // "";
	return $self->{returnType} . " " . $className . $self->{name} . "(" . $self->{params} . ")";
}

sub getDoxygenComment{
	my $self = shift;
	my $className = shift;
	my $prefix = "";
	if($self->isNewFunction()){
		$prefix = $constructorPrefix;
	}
	my $result = "";
	if($self->isValidFunction($className)){
		my $comment = $self->getComment();
		$result .= "/**\n";
		$result .= " * \\fn " . $prefix . $self->getPureFunction($className) . "\n";
		$result .= " * \\memberof $className\n";
		$result .= " " . $self->getComment();
		$result .= "*/\n\n";
	}
	return $result;
}

sub privateGetFunction{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $params = shift;
	my $isFirstArgumentConst = isFirstArgumentConst($params);

	if(not ($params =~ s/^[^,]*,/$className * $variableName,/)){
		$params = $className . " * " . $variableName;
	}
	if($isFirstArgumentConst){
		$params = "const " . $params;
	}
	return sprintf "%s %s_%s(%s)", $self->{returnType}, $className, $self->{name}, $params;
}

sub privateGetFunctionForValueParams{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $params = shift;
	my $castPrefix = shift;
	if(not ($params =~ s/$matchName\s*(,|$)/$variableName$2/)){
		$params = $variableName;
	}
	return sprintf "%s_%s((%s%s *) %s)", $className, $self->{name}, $castPrefix, $className, $params;
}

sub getHeaderPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $function = $self->privateGetFunction($className, $variableName, $self->{params});
	return $function . ";\n";
}

sub getImplForChildClassPrintable{
	my $self = shift;
	my $className = shift;
	my $variableName = shift;
	my $superClass = shift;
	my $params = $self->{params};
	my $castPrefix = "";
	if(isFirstArgumentConst($params)){
		$castPrefix = "const ";
	}

	$params = normalizeParams($params);
	my $function = $self->privateGetFunction($className, $variableName, $params) . "{\n\t";
	$params = convertParamsToValues($params);
	if(not ($self->{returnType} eq "void")){
		$function = $function . "return ";
	}

	$function = sprintf "%s%s;\n}\n\n", $function, $self->privateGetFunctionForValueParams($superClass, $variableName, $params, $castPrefix);
	return $function;
}

sub isVoidFunction{
	my $self = shift;
	if($self->{returnType} eq "void"){
		return 1;
	}else{
		return 0;
	}
}

sub getExeEventImplementationPrintable{
	my $self = shift;
	my $eventName = shift;
	my $delegateName = shift;
	my $listName = shift;
	my $variableName = shift;
	my $functionName = $self->{name};
	my $header = $self->privateGetFunction($eventName, $variableName, $self->{params});

	my $params = normalizeParams($self->{params});
	$params = convertParamsToValues($params);
	if(not ($params =~ s/^[^,]*,/delegate,/)){
		$params = "delegate";
	}
	my $str =
	"${header}{\n" .
	"\t$delegateName * delegate;\n" .
	"\tfor (size_t i = 0; i < IAStructArrayList_getCurrentSize(${variableName}->$listName); i++) {\n" .
	"\t\tdelegate = IAStructArrayList_get(${variableName}->$listName, i);\n" .
	"\t\t${delegateName}_$functionName($params);\n" .
	"\t}\n" .
	"}\n\n";
	return $str;
}

1;
