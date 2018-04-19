#!/usr/bin/perl

use strict;
use warnings;

package Expressions;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw($matchName $matchNameAndExtension $matchTypeRaw $matchType $matchParamsRaw $matchParams $matchFunction $matchParamWithNameRaw);

our $matchNameRaw = qr/\w[\w\d]*(?![\w\d])(?:\s*\[(?:\d*|\w[\w\d]*)\])*(?!\s*\[(?:\d*|\w[\w\d]*)\])/;
our $matchName = qr/(\w[\w\d]*)(?![\w\d])(?:\s*\[(?:\d*|\w[\w\d]*)\])*(?!\s*\[(?:\d*|\w[\w\d]*)\])/;
our $matchNameAndExtension = qr/(\w[\w\d]*)(?![\w\d])((?:\s*\[(?:\d*|\w[\w\d]*)\])*)(?!\s*\[(?:\d*|\w[\w\d]*)\])/;

our $matchTypeRaw = qr/(?:(?:const|struct|union|enum|volatile|auto|unsigned)\s+)*$matchNameRaw(?:\s*\*)*(?!\s*\*)/;
our $matchType = qr/($matchTypeRaw)/;

our $matchParams1 = qr/(?:[^\(\)]*\([^\(\)]*\))*[^\(\)]*/;
our $matchParams2 = qr/(?:[^\(\)]*\($matchParams1\))*[^\(\)]*/;
our $matchParams3 = qr/(?:[^\(\)]*\($matchParams2\))*[^\(\)]*/;
our $matchParams4 = qr/(?:[^\(\)]*\($matchParams3\))*[^\(\)]*/;
our $matchParams5 = qr/(?:[^\(\)]*\($matchParams4\))*[^\(\)]*/;
our $matchParams6 = qr/(?:[^\(\)]*\($matchParams5\))*[^\(\)]*/;
our $matchParamsRaw = qr/(?:[^\(\)]*\($matchParams6\))*[^\(\)]*(?![^\(\)])/;
our $matchParams = qr/($matchParamsRaw)/;

# 1...return type; 2...function name; 3...params
our $matchFunctionRaw = qr/$matchTypeRaw\s*\(\s*\*$matchNameRaw\s*\)\s*\($matchParamsRaw\)/;
our $matchFunction = qr/$matchType\s*\(\s*\*$matchName\s*\)\s*\($matchParams\)/;

our $matchParamWithNameRaw = qr/(?:$matchFunctionRaw|$matchTypeRaw\s*$matchNameRaw)/;


1;
