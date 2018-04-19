#!/usr/bin/perl

use strict;
use warnings;

package Constants;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw($constructorPrefix $destructorPrefix);


our $constructorPrefix = "IA_CONSTRUCTOR ";
our $destructorPrefix = "IA_DESTRUCTOR ";


1;
