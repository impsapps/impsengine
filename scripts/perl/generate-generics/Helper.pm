#!/usr/bin/perl

use strict;
use warnings;

package Helper;

use Expressions;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(normalizeParams removeFirstParamFromParams convertParamsToValues inheritFunction);

our $matchUnnamedParamRaw = qr/$matchTypeRaw|$matchTypeRaw\s*\(\s*\*\s*\)\s*\($matchParamsRaw\)/;

sub normalizeParams{
	my $params = shift;
	my $paramInt = 0;
	while($params =~ m/^((?:\s*$matchParamWithNameRaw\s*,)*?\s*)($matchUnnamedParamRaw)(\s*(?:,\s*(?:$matchUnnamedParamRaw|$matchParamWithNameRaw)\s*)*)\s*$/){
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
    $params =~ s/^\s*($matchParamWithNameRaw|$matchUnnamedParamRaw)\s*(,?\s*|$)//;
    return $params;
}

sub convertParamsToValues{
	my $params = shift;
	my $convertedParams = "";
	my $isFirstParam = 0;
	while($params =~ m/$matchSingleNormalizedParam/g){
		my $nextParam = $1;
		if($nextParam =~ m/^$matchType\s*$matchName$/){
			$nextParam = $2;
		}elsif($nextParam =~ m/^$matchFunction$/){
			$nextParam = $2;
		}else{
			die "Internal Error in convert Params to Values";
		}
		if($isFirstParam == 0){
			$isFirstParam = 1;
			$convertedParams = $nextParam;
		}else{
			$convertedParams = $convertedParams . ", " . $nextParam;
		}
	}
	return $convertedParams;
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
