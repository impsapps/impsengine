#!/usr/bin/perl

use strict;
use warnings;

package Class;

require Exporter;
our @ISA = qw(Exporter);

use Expressions;
use Function;

sub new{
	my $class = shift;
	my $className = shift;
	my $filePath = shift;
	my $self = {
		className => $className,
		superClassName => "",
		firstAttribute => undef,
		allAttributeNames => [],
		setters => [],
		settersAsRef => [],
		settersAsCharArray => [],
		getters => [],
		gettersAsConst => [],
		gettersAsRef => [],
		gettersAsConstRef => [],
		gettersAsCharArray => [],
		respondsTos =>[],
		exes => [],
		locks => [],
		registers => [],
		attributes => {},
		functions => [],
		isDelegate => 0,
		isEvent => 0,
		isEventWithoutRetain => 0,
		resourceProviders => [],
		yaml => undef,
		filePath => $filePath
	};
	bless $self, $class;
	return $self;
}

sub isValidClass{
	my $self = shift;
	my $objectVariableName = $self->getObjectVariableName();
	if($objectVariableName eq ""){
		return 0;
	}else{
		return 1;
	}
}

sub getClassName{
	my $self = shift;
	return $self->{className};
}

sub getSuperClassName{
	my $self = shift;
	return $self->{superClassName};
}

sub getAttribute{
	my $self = shift;
	my $attributeName = shift;
	return $self->{attributes}->{$attributeName};
}

sub isObject{
	my $self = shift;
	if ($self->getSuperClassName ne "") {
		return 1;
	}else{
		return 0;
	}
}

sub isStruct{
	my $self = shift;
	my @makeFunctions = $self->getMakeFunctionsForStruct();
	if (@makeFunctions > 0) {
		return 1;
	}else{
		return 0;
	}
}

sub isDelegate{
	my $self = shift;
	return $self->{isDelegate};
}

sub isEvent{
	my $self = shift;
	if ($self->{isEvent} == 1 || $self->{isEventWithoutRetain} == 1){
		return 1;
	}else{
		return 0;
	}
}

sub getResourceProviders{
	my $self = shift;
	return @{$self->{resourceProviders}};
}

sub getFilePath{
	my $self = shift;
	return $self->{filePath};
}

sub addExeFunctionsToList{
	my $self = shift;
	my $objectVariableName = shift;
	my $listRef = shift;
	my $className = shift // $self->{className};

	foreach my $function (@{$self->{functions}}){
		my $functionName = $function->{name};
		if($functionName =~ m/^exe/){
			push @$listRef, $function;
		}
	}

	foreach my $exe(@{$self->{exes}}){
		my $attribute = $self->{attributes}->{$exe};
		my $newFunctionHeader = $attribute->getExePrintable($className, $objectVariableName);
		our $newFunction = Function->new();
		$newFunction->initWithHeader($className, $newFunctionHeader);
		push @$listRef, $newFunction;
	}
}

sub getObjectVariableName{
	my $self = shift;
	foreach my $function (@{$self->{functions}}){
		my $className = $self->{className};
		my $objectVariableName = $function->{params};
		if($objectVariableName =~ m/^\s*$className\s*\*\s*$matchName/){
			return $1;
		}elsif($objectVariableName =~ m/^\s*$className\s*\*/){
			return "this";
		}
	}
	if($self->hasAnnotations()){
		return "this";
	}else{
		return "";
	}
}

sub getMakeFunctionsForStruct{
	my $self = shift;
	my $className = $self->getClassName();
	my @functions = ();
	foreach my $function (@{$self->{functions}}){
		if($function->isMakeFunction() && $function->isStaticFunction($className) == 1 && $function->{returnType} eq $className){
			push @functions, $function;
		}
	}
	return @functions;
}

sub getValidMakeFunctions{
	my $self = shift;
	my $className = $self->getClassName();
	my @functions = ();
	foreach my $function (@{$self->{functions}}){
		if($function->isMakeFunction() && $function->isValidFunction($className) == 1){
			push @functions, $function;
		}
	}
	return @functions;
}

sub getValidInitFunctions{
	my $self = shift;
	my $className = $self->getClassName();
	my @functions = ();
	foreach my $function (@{$self->{functions}}){
		if($function->isInitFunction() && $function->isValidFunction($className) == 1){
			push @functions, $function;
		}
	}
	return @functions;
}

sub getDeinitFunction{
	my $self = shift;
	foreach my $function (@{$self->{functions}}){
		if($function->isDeinitFunction()){
			return $function;
		}
	}
	return undef;
}

sub getAllNonSpecialValidFunctions{
	my $self = shift;
	my @result = ();
	foreach my $function (@{$self->{functions}}){
		if((not $function->isSpecialFunction()) && $function->isValidFunction($self->getClassName())){
			push @result, $function;
		}
	}
	return @result;
}

sub getAllSetterAttributeNames{
	my $class = shift;
	return (@{$class->{setters}}, @{$class->{settersAsRef}}, @{$class->{settersAsCharArray}});
}

sub hasAnnotations{
	my $class = shift;
	if($class->{superClassName} ne ""){
		return 1;
	}
	if(scalar (keys @{$class->{setters}})){
		return 1;
	}
	if(scalar (keys @{$class->{settersAsRef}})){
		return 1;
	}
	if(scalar (keys @{$class->{settersAsCharArray}})){
		return 1;
	}
	if(scalar (keys @{$class->{getters}})){
		return 1;
	}
	if(scalar (keys @{$class->{gettersAsConst}})){
		return 1;
	}
	if(scalar (keys @{$class->{gettersAsRef}})){
		return 1;
	}
	if(scalar (keys @{$class->{gettersAsConstRef}})){
		return 1;
	}
	if(scalar (keys @{$class->{gettersAsCharArray}})){
		return 1;
	}
	if(scalar (keys @{$class->{respondsTos}})){
		return 1;
	}
	if(scalar (keys @{$class->{exes}})){
		return 1;
	}
	if(scalar (keys @{$class->{locks}})){
		return 1;
	}
	if(scalar (keys @{$class->{registers}})){
		return 1;
	}
	if($class->{isEvent}){
		return 1;
	}
	if($class->{isEventWithoutRetain}){
		return 1;
	}
	return 0;
}

1;
