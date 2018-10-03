#!/usr/bin/perl

use strict;
use warnings;

package Constants;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw($constructorMacro $destructorMacro $copyright);


our $constructorMacro = "IA_CONSTRUCTOR";
our $destructorMacro = "IA_DESTRUCTOR";

our $copyright = "//  \n" .
"//  This file has been automatically generated. DO NOT EDIT IT.\n" .
"//  \n";

1;
