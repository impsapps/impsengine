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
	my $self = {
		className => shift,
		superClassName => "",
		firstAttribute => undef,
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
		yaml => undef
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

sub isObject{
	my $self = shift;
	if ($self->getSuperClassName ne "") {
		return 1;
	}else{
		return 0;
	}
}

sub isDelegate{
	my $self = shift;
	return $self->{isDelegate};
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
		our $newFunction = new Function();
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
