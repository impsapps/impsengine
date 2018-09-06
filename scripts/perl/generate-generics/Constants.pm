#!/usr/bin/perl

use strict;
use warnings;

package Constants;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw($constructorPrefix $destructorPrefix $copyright);


our $constructorPrefix = "IA_CONSTRUCTOR ";
our $destructorPrefix = "IA_DESTRUCTOR ";

our $copyright = "//  \n" .
"//  This file has been automatically generated. DO NOT EDIT IT.\n" .
"//  \n";

1;
