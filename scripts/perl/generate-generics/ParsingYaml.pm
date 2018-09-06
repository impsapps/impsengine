#!/usr/bin/perl

use strict;
use warnings;

package ParsingYaml;

use YAML::XS "LoadFile";
use Class;
use Attribute;
use Expressions;
use Function;
use Helper;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getClassNameForYamlFile preParseYamlFile getYamlFilesForDir);

sub getClassNameForYamlFile {
	my $path = shift;
	(my $className = $path) =~ s/.*\/(.*)\.yaml/$1/;
	return $className;
}

sub privateIsValidYamlFile {
	my $name = shift;
	if (substr ($name, 0, 1) eq '.'){
		return 0;
	}elsif(not $name =~ m/\.yaml$/){
		return 0;
	}else{
		return 1;
	}
}

sub getYamlFilesForDir {
	my $dir = shift;
	my @files = ();

	opendir(DH, $dir) or die "Could not read from dir $dir.";
	my @names = readdir(DH);
	closedir(DH);

	foreach my $name (@names){
		my $newName = $dir . '/' . $name;

		if(-f $newName){
			if(privateIsValidYamlFile($name)){
				push @files, $newName;
			}
		}
	}
	return @files;
}

sub preParseYamlFile {
  my $yamlFile = shift;
  my $yaml = LoadFile $yamlFile;
	die "Expected a hash on top level of yaml file \"$yamlFile\"" if (ref $yaml ne 'HASH');
  die "Expected key \"__generate__\" or \"__template__\" on top level of yaml file \"$yamlFile\"" if (not (exists $yaml->{__generate__} or exists $yaml->{__template__}));
	my $className = getClassNameForYamlFile($yamlFile);
  my $class = Class->new($className);
	$class->{yaml} = $yaml;
  return $class;
}

1;

