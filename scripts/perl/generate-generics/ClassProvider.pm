#!/usr/bin/perl

use strict;
use warnings;


# A class provider lazily parses header files as needed and provides the classes within.

package ClassProvider;

use Parsing;

sub new{
  my $class = shift;
  my $self = {
    classes => {},
    pendingHeaderFiles => {}
  };
  bless $self, $class;
  return $self;
}

sub addHeaderFile{
  my $self = shift;
  my $headerFile = shift;
  my $className = getClassNameWithExtensionForHeaderFile($headerFile);
  $self->{pendingHeaderFiles}->{$className} = $headerFile;
}

sub addHeaderFileDir{
  my $self = shift;
  my $headerFileDir = shift;
  my @headerFiles = getHeaderFilesForDir($headerFileDir);
  foreach my $headerFile (@headerFiles){
    $self->addHeaderFile($headerFile);
  }
}

sub getClass{
  my $self = shift;
  my $className = shift;
  return undef if ($className =~ m/\+/);

  if (exists $self->{classes}->{$className}) {
    return $self->{classes}->{$className};
  }
  if (exists $self->{pendingHeaderFiles}->{$className}) {
    my $class = parseFile($self->{pendingHeaderFiles}->{$className});
    die "Could not parse class \"$className\"." if (not $class);
    $self->{classes}->{$className} = $class;
    return $class;
  }
  return undef;
}

1;
