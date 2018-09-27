#!/usr/bin/perl

use strict;
use warnings;

package Helper;

use Expressions;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(normalizeParams removeFirstParamFromParams listAllParams listAllParamNames getParamName convertParamsToValues inheritFunction);

our $matchUnnamedParamRaw = qr/$matchTypeRaw|$matchTypeRaw\s*\(\s*\*\s*\)\s*\($matchParamsRaw\)/;

sub normalizeParams{
	my $params = shift;
	my $paramInt = 0;
	while($params =~ m/^((?:\s*$matchSingleNormalizedParamRaw\s*,)*?\s*)($matchUnnamedParamRaw)(\s*(?:,\s*(?:$matchUnnamedParamRaw|$matchSingleNormalizedParamRaw)\s*)*)\s*$/){
		my $begin = $1;
		my $mid = $2;
		my $end = $3;
		my $newName = "param" . $paramInt;
		if($mid =~ m/^$matchType$/){
			$mid = $mid . " " . $newName;
		}else{
			$mid =~ m/^($matchTypeRaw\s*\(\s*\*)(\s*\)\s*\($matchParamsRaw\))$/;
			$mid = $1 . $newName . $2;
		}
		$params = $begin . $mid . $end;
		$paramInt ++;
	}
	return $params;
}

sub removeFirstParamFromParams{
    my $params = shift;
    $params =~ s/^\s*($matchSingleNormalizedParamRaw|$matchUnnamedParamRaw)\s*(,?\s*|$)//;
    return $params;
}

sub listAllParams{
	my $params = shift;
	my @result = ();
	while($params =~ m/$matchSingleNormalizedParam/g){
		my $nextParam = $1;
		push @result, $nextParam;
	}
	return @result;
}

sub listAllParamNames{
	my $params = shift;
	my @result = ();
	foreach my $nextParam(listAllParams($params)){
		push @result, getParamName($nextParam);
	}
	return @result;
}

sub getParamName{
	my $param = shift;
	if($param =~ m/^$matchType\s*$matchName$/){
		$param = $2;
	}elsif($param =~ m/^$matchFunction$/){
		$param = $2;
	}else{
		die "Internal error. Expected param to be a type or function.";
	}
	return $param;
}

sub convertParamsToValues{
	my $params = shift;
	my @allParamNames = listAllParamNames($params);
	my $result = join(", ", @allParamNames);
	return $result;
}

sub inheritFunction{
	my $function = shift;
	my $className = shift;
	my $variableName = shift;
	if($function =~ m/($matchType|$matchFunction)\s*$matchName\s*\($matchParams\)\s*;/){
		my $returnType = $1;
		my $params = $7;
		my $functionName = $6;
		if($functionName =~ m/([^_]*)_$matchName/){
			my $superClassName = $1;
			$functionName = $2;
			my $function = new Function($functionName, $returnType, $params);
			my $header = $function->getHeaderPrintable($className, $variableName);
			my $impl = $function->getImplForChildClassPrintable($className, $variableName, $superClassName);
			return ($header, $impl);
		}
	}else{
		die "Internal Error in inheritFunction";
	}
}

1;
