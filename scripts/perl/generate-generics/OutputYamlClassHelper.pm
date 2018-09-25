package OutputYamlClassHelper;
use strict;
use warnings FATAL => 'all';

use Expressions;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getParamNamesForYamlNode canCompleteYamlNames);

sub privateIsSpecialYamlKey{
  my $key = shift;
  if ($key =~ m/^__.+__$/){
    return 1;
  }else{
    return 0;
  }
}

sub getParamNamesForYamlNode{
  my $yamlNode = shift;
  my @yamlNames = ();
  foreach my $key (keys %$yamlNode){
    if (not privateIsSpecialYamlKey($key)){
      if ($key =~ m\^$matchName->$matchName$\) {
        my $matchedYamlName = $1;
        push @yamlNames, $matchedYamlName;
      }else{
        push @yamlNames, $key;
      }
    }
  }
  return @yamlNames;
}

sub canCompleteYamlNames{
  my $yamlNamesRef = shift;
  my $requiredNamesRef = shift;
  my $optionalNamesRef = shift // \();
  my @yamlNames = @$yamlNamesRef;

  foreach my $requiredName (@$requiredNamesRef){
    my $wasRequiredNameFound = 0;
    foreach my $index (0 .. $#yamlNames){
      if ($requiredName eq $yamlNames[$index]){
        splice @yamlNames, $index, 1;
        $wasRequiredNameFound = 1;
        last;
      }
    }
    if ($wasRequiredNameFound == 0) {
      return 0;
    }
  }
  foreach my $yamlName (@yamlNames){
    my $isYamlNameInOptionalNames = 0;
    foreach my $optionalName (@$optionalNamesRef){
      if ($yamlName eq $optionalName) {
        $isYamlNameInOptionalNames = 1;
        last;
      }
    }
    if ($isYamlNameInOptionalNames == 0) {
      return 0;
    }
  }
  return 1;
}

1;
