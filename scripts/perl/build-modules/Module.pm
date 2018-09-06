#!/usr/bin/perl

package Module;

use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(setupModuleWithAbsolutePathToRootDirAndCWD);

use Storable qw(dclone);

use Constants;


my $absolutePathToRootDir = "";
my $cwd = "";

sub setupModuleWithAbsolutePathToRootDirAndCWD{
  $absolutePathToRootDir = shift;
  $cwd = shift;
  if ($absolutePathToRootDir eq "/"){
    $absolutePathToRootDir = "";
  }
}

sub new{
  my $class = shift;
  my $name = shift;
  my $structure = shift;
  my $path = shift;
  my $self = dclone($structure);
  $self->{"name"} = $name;
  $self->{"path"} = $path;
  if($self->{"path"} ne ""){
    $self->{"path"} = $self->{"path"} . "/";
  }
  bless $self, $class;

  if(exists ($self->{"c"})){
    foreach my $folderName (@{$self->{"c"}}){
      if (not $folderName eq $sharedSourceFolder) {
        my $isValid = 0;
        foreach my $possibleSourceFolderName (@possibleSourceFolderNames){
          if ($folderName eq $possibleSourceFolderName) {
            $isValid = 1;
            last;
          }
        }
        die "$folderName is not a valid source folder name for module $name." if ($isValid == 0);
      }
      die "$folderName is not available for module $name which was specified." if (not $self->hasCSourceFolders($folderName));
    }
  }
  return $self;
}

sub getName{
  my $self = shift;
  return $self->{"name"};
}

sub getGroup{
  my $self = shift;
  $self->{"path"} =~ m/([^\/]*)\/$/;
  my $moduleGroup = $1;
  if ($moduleGroup eq ""){
    $moduleGroup = "nil";
  }
  return $moduleGroup;
}

sub getDependencies{
  my $self = shift;
  my $platform = shift // "";
  if ($platform eq ""){
    if(exists $self->{"dep"}){
	  return @{$self->{"dep"}};
    }
  } else {
	if(exists $self->{$platform . "-dep"}){
	  return @{$self->{$platform . "-dep"}};
    }
  }
  return ();
}

sub hasCSourceFolders{
  my $self = shift;
  my $folderName = shift;
  if(not exists ($self->{"c"})){
    return 0;
  }
  my $cSourceFolders = $self->{"c"};
  foreach my $cSourceFolder (@$cSourceFolders){
    if($cSourceFolder eq $folderName){
      my @folders = $self->getCSourceFolders($folderName);
      return scalar @folders;
    }
  }
  return 0;
}

sub getCSourceFolders{
  my $self = shift;
  my $folderName = shift;
  my $dir = $self->getCGroupPath();
  opendir(my $dh, $dir) or die "Could not read from dir $dir.";
	my @names = readdir($dh);
	closedir($dh);
  my @folders = ();
  foreach my $name (@names) {
    if ($name =~ m/(^|\+)$folderName($|\+)/) {
      push @folders, $dir . "/" . $name;
    }
  }
  return @folders;
}

sub getCGroupPath{
  my $self = shift;
  my $groupPath = $absolutePathToRootDir . "/" . $self->{"path"} . $self->{"name"} . "/c";
  return $groupPath;
}

sub getJavaSourceFolder{
  my $self = shift;
  my $modulePath = $self->{"path"};
  return $absolutePathToRootDir . "/" . $modulePath . $self->{"name"} . "/java";
}

sub getExternalIncludeDirs{
  my $self = shift;
  if (exists $self->{"external-include-dirs"}) {
    return @{$self->{"external-include-dirs"}};
  } else {
    return ();
  }
}

sub getExternalSrcFiles{
  my $self = shift;
  if (exists $self->{"external-src-files"}) {
    return @{$self->{"external-src-files"}};
  } else {
    return ();
  }
}

sub shouldGenerateGenerics{
  my $self = shift;
  if ($self->{"no-generics"}) {
    return 0;
  } else {
    return 1;
  }
}

1;
