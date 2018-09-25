package ResourceProvider;
use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);

sub new{
  my $class = shift;
  my $resourceName = shift;
  my $className = shift;
  my $function = shift;
  my $self = {
    resourceName => $resourceName,
    className => $className,
    function => $function
  };
  bless $self, $class;
  return $self;
}

sub getResourceName{
  my $self = shift;
  return $self->{resourceName};
}

sub getClassName{
  my $self = shift;
  return $self->{className};
}

sub getFunction{
  my $self = shift;
  return $self->{function};
}

1;