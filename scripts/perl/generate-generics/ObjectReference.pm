package ObjectReference;
use strict;
use warnings;

sub new{
  my $class = shift;
  my $refName = shift;
  my $type = shift;
  my $self  = {
    refName => $refName,
    type => $type,
    attributesClassNameForInjection => "",
  };
  bless $self, $class;
  return $self;
}

sub getRefName{
  my $self = shift;
  return $self->{refName};
}

sub hasType{
  my $self = shift;
  my $type = shift;
  if ($type eq $self->getType()) {
    return 1;
  }else{
    return 0;
  }
}

sub getType{
  my $self = shift;
  return $self->{type};
}

sub makeInjectable{
  my $self = shift;
  my $attributeClassName = shift;
  $self->{attributesClassNameForInjection} = $attributeClassName;
}

sub isInjectable{
  my $self = shift;
  if ($self->{attributesClassNameForInjection}) {
    return 1;
  }else{
    return 0;
  }
}

sub getAttributesClassNameForInjection{
  my $self = shift;
  return $self->{attributesClassNameForInjection};
}


1;