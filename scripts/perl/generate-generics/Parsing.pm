#!/usr/bin/perl

use strict;
use warnings;

package Parsing;

use Class;
use Attribute;
use Expressions;
use Function;
use Helper;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(addClassForFile addClasses getObjectVariableName getHeaderFilesForDir);

my $matchComment = qr/(?:\/\*((?:.|\s)*?)\*\/|\/\/([^\n]*))/;
my $matchAnnotationInCommand = qr/@([^@]*)/;
my $matchSeperateAnnotationAndInfo = qr/^([^:]*?)(?::((?:.|\n)*?))?\s*$/;

sub getCommentContent {
	if(defined $1){
		return $1;
	}else{
		return $2;
	}
}

sub addClassForFile {
	my $path = shift;
	my $classes = shift;
	if ($path =~ m/(.*)\.h$/){
		open FILE, "<", $path or die "unknown error: couldn't open file for reading";
		$/ = ";";

		(my $className = $path) =~ s/.*\/(.*)\.h/$1/;
		if(index($className, '+') != -1){
			if($className =~ m/\+Generated$/){
				return
			}
			$className =~ m/([^+]*)\+/;
			$className = $1;
			my $isFunctionNameCheckDisabled = 0;
			while(my $command = <FILE>){
				my $comment = "";
				while($command =~ s/$matchComment//){
					$comment = getCommentContent();
					while($comment =~ m/$matchAnnotationInCommand/g){
						$1 =~ m/$matchSeperateAnnotationAndInfo/;
						my $annotation = $1;
						my $info = $2;
						if(not defined($info)){
							$info = "";
						}
						if($info eq ""){
							my @splited = split /\s*\+\s*/, $annotation;
							foreach my $a (@splited){
								if($a eq "disableFunctionNameCheck"){
									$isFunctionNameCheckDisabled = 1;
								}else{
									die sprintf("Invalid annotation in class extension %s in file %s.\n", $a, $path);
								}
							}
						}else{

							if($annotation eq "description"){

							}elsif($annotation =~ m/param\s*[\w\d]*/){

							}else{
								die sprintf("Invalid annotation %s with information %s in in class extension %s.\n", $annotation, $info, $path);
							}
						}
					}
				}

				my $tempFunction = new Function();
				my $returnCode = $tempFunction->initWithHeader($className, $command, $comment);
				if($returnCode == 2){
					if($isFunctionNameCheckDisabled == 0){
						die sprintf("Invalid function name: %s in file %s.\n", $tempFunction->{name}, $path);
					}
				}
			}
			return;
		}


		my $class = new Class($className);
		my $isScanningClassAttributes = 0;

		my $structNameDefinition = "";
		my $isTypedef = 0;

		my $isFunctionNameCheckDisabled = 0;

		my $isFirstAttribute = 1;

        COMMAND_LOOP:
		while(my $command = <FILE>){
			my $annotationSet = 0;
			my $annotationSetAsRef = 0;
			my $annotationSetAsCharArray = 0;
			my $annotationGet = 0;
			my $annotationGetAsConst = 0;
			my $annotationGetAsRef = 0;
			my $annotationGetAsConstRef = 0;
			my $annotationGetAsCharArray = 0;
			my $annotationRespondsTo = 0;
			my $annotationExe = 0;
			my $annotationLock = 0;
			my $annotationRegister = 0;
			my $annotationEvent = 0;
			my $annotationExtend = 0;
			my $comment = "";

			while($command =~ s/$matchComment//){
				$comment = getCommentContent();
				while($comment =~ m/$matchAnnotationInCommand/g){
					$1 =~ m/$matchSeperateAnnotationAndInfo/;
					my $annotation = $1;
					my $info = $2;

					if(not defined($info)){
						$info = "";
					}

					if($info eq ""){
						my @splited = split /\s*\+\s*/, $annotation;
						foreach my $a (@splited){
							if($a eq "set"){
								$annotationSet = 1;
							}elsif($a eq "setAsRef"){
								$annotationSetAsRef = 1;
							}elsif($a eq "setAsCharArray"){
								$annotationSetAsCharArray = 1;
							}elsif($a eq "get"){
								$annotationGet = 1;
							}elsif($a eq "getAsConst"){
								$annotationGetAsConst = 1;
							}elsif($a eq "getAsRef"){
								$annotationGetAsRef = 1;
							}elsif($a eq "getAsConstRef"){
								$annotationGetAsConstRef = 1;
							}elsif($a eq "getAsCharArray"){
								$annotationGetAsCharArray = 1;
							}elsif($a eq "respondsTo"){
								$annotationRespondsTo = 1;
							}elsif($a eq "exe"){
								$annotationExe = 1;
							}elsif($a eq "lock"){
								$annotationLock = 1;
							}elsif($a eq "register"){
								$annotationRegister = 1;
							}elsif($a eq "event"){
								$annotationEvent = 1;
							}elsif($a eq "extend"){
								$annotationExtend = 1;
                            }elsif($a eq "disableFunctionNameCheck"){
                                $isFunctionNameCheckDisabled = 1;
                            }elsif($a eq "ignore"){
                                $class = new Class($className);
                                last COMMAND_LOOP;
                            }else{
								die sprintf("Invalid annotation %s in file %s.\n", $a, $path);
							}
						}
					}else{
						$annotation =~ m/^\s*(.*?)\s*$/;
						$annotation = $1;
						$info =~ m/^\s*(.*?)\s*$/;
						$info = $1;

						if($annotation eq "description"){

						}elsif($annotation =~ m/param\s*[\w\d]*/){

						}else{
							die sprintf("Invalid annotation %s with information %s in file %s.\n", $annotation, $info, $path);
						}
					}
				}
			}

			if($isScanningClassAttributes == 0 && $class->{attributes} != 0){
				my $shouldContinue = 0;
				if ($command =~ m/typedef\s+struct.*\{(.*)/s){
					$isTypedef = 1;
					$shouldContinue = 1;
				} elsif ((not $structNameDefinition eq "") && $command =~ m/struct\s+$structNameDefinition\s*\{(.*)/s){
					$isTypedef = 0;
					$shouldContinue = 1;
				}

				if($command =~ m/typedef\s+struct\s+([\w\d]+)\s+$className/){
					$structNameDefinition = $1;
				}

				if($shouldContinue){
					$command =~ m/\{(.*)/s;
					$isScanningClassAttributes = 1;
					$isFirstAttribute = 1;
					$command = $1;
					if($annotationEvent == 1){
						$class->{isEvent} = 1;
					}
				}
			}

			if($isScanningClassAttributes == 1){
				if(index($command, '}') != -1){
					if(($isTypedef && $command =~ m/\}\s*${className}\s*;/) || $isTypedef == 0){
						if ($className =~ m/Delegate$/) {
							$class->{isDelegate} = 1;
							if (! $class->{firstAttribute} || $class->{firstAttribute}->isObjectPointer() == 0) {
								die sprintf("Delegate does not start with an object pointer: %s in file %s.\n", $className, $path);
							}
						}
						if($class->{isEvent} == 1 && (! $class->{isDelegate})){
							die sprintf("Annotation \@event is only applicable on delegates. The name of delegates must end on \"Delegate\": %s in file %s.\n", $className, $path);
						}
					}else{
						#reset class;
						$class = new Class($className);
					}
					$isScanningClassAttributes = 0;
				}else{
					my $attribute = new Attribute($command);
					if(!$attribute){
						die sprintf("Cannot parse attribute: %s in file %s. Please notice that incomplete types are not allowed in structs.\n", $command, $path);
					}
					$class->{attributes}->{$attribute->{name}} = $attribute;
					if ($isFirstAttribute) {
						$class->{firstAttribute} = $attribute;
						if($annotationExtend == 1){
							my $shouldDie = 1;
							if($attribute->{type} =~ m/^(\w[\w\d]+)$/){
								if($1){
									$class->{superClassName} = $attribute->{type};
									$shouldDie = 0;
								}
							}
							if($shouldDie == 1){
								die sprintf("Cannot extend type %s in class %s\n", $attribute->{type}, $path);
							}
							$annotationExtend = 0;
						}
					}

					my $attributeName = $attribute->{name};
					if($annotationSet == 1){
						push(@{$class->{setters}}, $attributeName);
					}
					if($annotationSetAsRef == 1){
						push(@{$class->{settersAsRef}}, $attributeName);
					}
					if($annotationSetAsCharArray == 1){
						push(@{$class->{settersAsCharArray}}, $attributeName);
					}
					if($annotationGet == 1){
						push(@{$class->{getters}}, $attributeName);
					}
					if($annotationGetAsConst == 1){
						push(@{$class->{gettersAsConst}}, $attributeName);
					}
					if($annotationGetAsRef == 1){
						push(@{$class->{gettersAsRef}}, $attributeName);
					}
					if($annotationGetAsConstRef == 1){
						push(@{$class->{gettersAsConstRef}}, $attributeName);
					}
					if($annotationGetAsCharArray == 1){
						push(@{$class->{gettersAsCharArray}}, $attributeName);
					}
					if($annotationRespondsTo == 1){
						if($attribute->{isFunctionPointer} == 1){
							push(@{$class->{respondsTos}}, $attributeName);
						}else{
							die sprintf("RespondsTo keyword used for non function %s in class %s\n", $attributeName, $path);
						}
					}
					if($annotationExe == 1){
						if($attribute->{isFunctionPointer} == 1){
							if($attribute->isValidExeFunction() == 1){
								push(@{$class->{exes}}, $attributeName);
							}else{
								die sprintf("Invalid execute function %s in class %s\n", $attributeName, $path);
							}
						}else{
							die sprintf("Cannot execute non function %s in class %s\n", $attributeName, $path);
						}
					}
					if($annotationLock == 1){
						push(@{$class->{locks}}, $attributeName);
					}
					if($annotationRegister == 1){
						push(@{$class->{registers}}, $attributeName);
					}
				}
				if($annotationExtend == 1){
					die sprintf("Error in file %s: Annotation extend is only at first attribute allowed!\n", $path);
				}
				$isFirstAttribute = 0;
				next;
			}
			my $tempFunction = new Function();
			my $returnCode = $tempFunction->initWithHeader($className, $command, $comment);
			if ($returnCode == 1){
				my $function = $tempFunction;
				if(index($function->{name}, "init") == 0){
					$class->{hasInitFunction} = 1;
				}
				push (@{$class->{functions}}, $function);
			}elsif($returnCode == 2){
				if($isFunctionNameCheckDisabled == 0){
					die sprintf("Invalid function name: %s in file %s.\n", $tempFunction->{name}, $path);
				}
			}elsif($returnCode == 3){
				die sprintf("Invalid function name! A function which start with deinit must not have any additional characters: %s in file %s.\n", $tempFunction->{name}, $path);
			}
		}
		close FILE;

		if ($class->{superClassName} ne ""){
			$class->{isObject} = 1;
		}
		$classes->{$className} = $class;
	}
}

sub privateShouldSkipName {
	my $name = shift;
	if (substr ($name, 0, 1) eq '.'){
		return 1;
	}else{
		return 0;
	}
}

sub privateShouldSkipFile {
	my $name = shift;
	if (privateShouldSkipName($name) == 1){
		return 1;
	}elsif(not $name =~ m/\.h$/){
		return 1;
	}else{
		return 0;
	}
}

sub privateShouldSkipDir {
	my $name = shift;
	if (privateShouldSkipName($name) == 1){
		return 1;
	}elsif($name eq "generics" or $name eq "generated-jni-headers"){
		return 1;
	}else{
		return 0;
	}
}

sub addClasses {
	my $dir = shift;
	my $classes = shift;

	opendir(DH, $dir) or die "Unable to open directory \"$dir\"!";
	my @names = readdir(DH);
	closedir(DH);

	foreach my $name (@names){
		my $newName = $dir . '/' . $name;
		if(-f $newName){
			if(privateShouldSkipFile($name) == 0){
				addClassForFile($newName, $classes);
			}
		}elsif(-d $newName){
			if(privateShouldSkipDir($name) == 0){
				addClasses($newName, $classes);
			}
		}
	}
	return 0;
}

sub getHeaderFilesForDir {
	my $dir = shift;
	my $files = [];

	opendir(DH, $dir);
	my @names = readdir(DH);
	closedir(DH);

	foreach my $name (@names){
		my $newName = $dir . '/' . $name;

		if(-f $newName){
			if(privateShouldSkipFile($name) == 0){
				push @{$files}, $name;
			}
		}elsif(-d $newName){
			if(privateShouldSkipDir($name) == 0){
				push @{$files}, @{getHeaderFilesForDir($newName)};
			}
		}
	}
	return $files;
}

1;
