#!/usr/bin/perl

use strict;
use warnings;

package ParsingHeader;

use Class;
use Attribute;
use Expressions;
use Function;
use Helper;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(getClassNameWithExtensionForHeaderFile parseHeaderFile getHeaderFilesForDir);

my $matchComment = qr/(?:\/\*((?:.|\s)*?)\*\/|\/\/([^\n]*))/;
my $matchAnnotationInCommand = qr/@([^@]*)/;
my $matchSeperateAnnotationAndInfo = qr/^([^:]*?)(?::((?:.|\n)*?))?\s*$/;


sub getClassNameWithExtensionForHeaderFile {
	my $path = shift;
	(my $className = $path) =~ s/.*\/(.*)\.h/$1/;
	return $className;
}

sub getCommentContent {
	if(defined $1){
		return $1;
	}else{
		return $2;
	}
}

sub privateIsValidHeaderFile {
	my $name = shift;
	if (substr ($name, 0, 1) eq '.'){
		return 0;
	}elsif(not $name =~ m/\.h$/){
		return 0;
	}else{
		return 1;
	}
}

sub getHeaderFilesForDir {
	my $dir = shift;
	my @files = ();

	opendir(DH, $dir) or die "Could not read from dir $dir.";
	my @names = readdir(DH);
	closedir(DH);

	foreach my $name (@names){
		my $newName = $dir . '/' . $name;

		if(-f $newName){
			if(privateIsValidHeaderFile($name)){
				push @files, $newName;
			}
		}
	}
	return @files;
}

sub parseHeaderFile {
	my $path = shift;

	die "Invalid path for parsing: $path" if (privateIsValidHeaderFile($path) == 0);

	open FILE, "<", $path or die "unknown error: couldn't open file \"$path\" for reading";
	$/ = ";";

	my $className = getClassNameWithExtensionForHeaderFile($path);
	if(index($className, '+') != -1){
		if($className =~ m/\+Generated$/){
			return undef;
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

			my $tempFunction = Function->new();
			my $returnCode = $tempFunction->initWithHeader($className, $command, $comment);
			if($returnCode == 2){
				if($isFunctionNameCheckDisabled == 0){
					die sprintf("Invalid function name: \"%s\" with type \"%s\" in file \"%s\".\n", $tempFunction->{name}, $tempFunction->{returnType}, $path);
				}
			}
		}
		return undef;
	}


	my $class = Class->new($className);
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
		my $annotationEventWithoutRetain = 0;
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
						}elsif($a eq "eventWithoutRetain"){
							$annotationEventWithoutRetain = 1;
						}elsif($a eq "extend"){
							$annotationExtend = 1;
						}elsif($a eq "disableFunctionNameCheck"){
							$isFunctionNameCheckDisabled = 1;
						}elsif($a eq "ignore"){
							$class = Class->new($className);
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
				if($annotationEventWithoutRetain == 1){
					$class->{isEventWithoutRetain} = 1;
				}
				if ($annotationEvent && $annotationEventWithoutRetain) {
					die "Cannot have both annotations \"event\" and \"eventWithoutRetain\": $className in file $path.\n";
				}
			}
		}

		if($isScanningClassAttributes == 1){
			if(index($command, '}') != -1){
				$command =~ m/\}\s*$matchName\s*;/;
				my $structName = $1;
				if(($isTypedef && $className eq $structName) || $isTypedef == 0){
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
					die "Annotations in non-class \"$structName\" found. File path: \"$path\"" if ($class->hasAnnotations());
					$class = Class->new($className);
				}
				$isScanningClassAttributes = 0;
			}else{
				my $attribute = Attribute->newWithCommand($command);

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
		my $tempFunction = Function->new();
		my $returnCode = $tempFunction->initWithHeader($className, $command, $comment);
		if ($returnCode == 1){
			push (@{$class->{functions}}, $tempFunction);
		}elsif($returnCode == 2){
			if($isFunctionNameCheckDisabled == 0){
				die sprintf("Invalid function name: \"%s\" with type \"%s\" in file \"%s\".\n", $tempFunction->{name}, $tempFunction->{returnType}, $path);
			}
		}elsif($returnCode == 3){
			die sprintf("Invalid function name! A function which start with deinit must not have any additional characters: \"%s\" with type \"%s\" in file \"%s\".\n", $tempFunction->{name}, $tempFunction->{returnType}, $path);
		}
	}
	close FILE;
	return $class;
}

1;
