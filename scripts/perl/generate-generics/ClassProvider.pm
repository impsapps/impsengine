#!/usr/bin/perl

use strict;
use warnings;


# A class provider lazily parses header files as needed and provides the classes within.

package ClassProvider;

use ParsingHeader;
use ParsingYaml;

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
  my $filePath = shift;
  my $className = getClassNameWithExtensionForHeaderFile($filePath);
  $self->{pendingHeaderFiles}->{$className} = $filePath;
}

sub addYamlFile{
  my $self = shift;
  my $filePath = shift;
  my $className = getClassNameForYamlFile($filePath);
  $self->{classes}->{$className} = preParseYamlFile($filePath);
}

sub addFileDir{
  my $self = shift;
  my $fileDir = shift;
  my @headerFiles = getHeaderFilesForDir($fileDir);
  foreach my $headerFile (@headerFiles){
    $self->addHeaderFile($headerFile);
  }
  my @yamlFiles = getYamlFilesForDir($fileDir);
  foreach my $yamlFile (@yamlFiles){
    $self->addYamlFile($yamlFile);
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
    my $class = parseHeaderFile($self->{pendingHeaderFiles}->{$className});
    die "Could not parse class \"$className\"." if (not $class);
    $self->{classes}->{$className} = $class;
    return $class;
  }
  return undef;
}

1;
