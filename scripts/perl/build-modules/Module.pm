#!/usr/bin/perl

package Module;

use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(setupModuleWithAbsolutePathToRootDirAndCWD);

use Storable qw(dclone);


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
    
    if ($self->shouldBuildSharedCSourceFolder()){
        if (not -d $self->getSharedCSourceFolder()){
            die "Module with name \"" . $self->{"name"} . "\" has no c shared folder which was specified!";
        }
    }
    
    if ($self->shouldBuildIOSCSourceFolder()){
        if (not -d $self->getIOSCSourceFolder()){
            die "Module with name \"" . $self->{"name"} . "\" has no c ios folder which was specified!";
        }
    }
    
    if ($self->shouldBuildAndroidCSourceFolder()){
        if (not -d $self->getAndroidCSourceFolder()){
            die "Module with name \"" . $self->{"name"} . "\" has no c android folder which was specified!";
        }
    }
    
    return $self;
}

sub getName{
    my $self = shift;
    return $self->{"name"};
}

sub getModuleGroup{
    my $self = shift;
    $self->{"path"} =~ m/([^\/]*)\/$/;
    my $moduleGroup = $1;
    if ($moduleGroup eq ""){
        $moduleGroup = "nil";
    }
    return $moduleGroup;
}

sub hasIncludes{
	my $self = shift;
	if(exists ($self->{"include"})){
		return 1;
	}else{
		return 0;
	}
}

sub getIncludes{
	my $self = shift;
	if(exists $self->{"include"}){
		return @{$self->{"include"}};
	}else{
		return ();
	}
}

sub privateShouldBuildFolderInCSource{
    my $self = shift;
    my $folderName = shift;
    if(not exists ($self->{"c"})){
        die "Module with name \"" . $self->{"name"} . "\" has no c source!";
    }
    my $cSourceFolders = $self->{"c"};
    my $hasFolderInCSource = 0;
    foreach my $cSourceFolder (@$cSourceFolders){
    	if($cSourceFolder eq $folderName){
    		$hasFolderInCSource = 1;
    	}
    }
    return $hasFolderInCSource;
}

sub shouldBuildSharedCSourceFolder{
    my $self = shift;
    return $self->privateShouldBuildFolderInCSource("shared");
}

sub shouldBuildAndroidCSourceFolder{
    my $self = shift;
    return $self->privateShouldBuildFolderInCSource("android");
}

sub shouldBuildIOSCSourceFolder{
    my $self = shift;
    return $self->privateShouldBuildFolderInCSource("ios");
}

sub privateGetShortedPath{
    my $self = shift;
    my $shortedPath = $self->{"path"};
    $shortedPath =~ s/modules\///;
    return $shortedPath;
}

sub getCSourceFolder{
    my $self = shift;
    my $modulePath = $self->{"path"};
    return $absolutePathToRootDir . "/" . $modulePath . $self->{"name"} . "/c";
}

sub getSharedCSourceFolder{
    my $self = shift;
    return $self->getCSourceFolder() . "/shared";
}

sub getAndroidIncludeFolder{
    my $self = shift;
    return $absolutePathToRootDir . "/include/android/" .  $self->privateGetShortedPath() . $self->{"name"};
}

sub getAndroidCSourceFolder{
    my $self = shift;
    return $self->getCSourceFolder() . "/android";
}

sub getIOSIncludeFolder{
    my $self = shift;
    return $absolutePathToRootDir . "/include/ios/" .  $self->privateGetShortedPath() . $self->{"name"};
}

sub getIOSCSourceFolder{
    my $self = shift;
    return $self->getCSourceFolder() . "/ios";
}

sub getWindowsIncludeFolder{
    my $self = shift;
    return $absolutePathToRootDir . "/include/windows/" .  $self->privateGetShortedPath() . $self->{"name"};
}

sub getWindowsCSourceFolder{
    my $self = shift;
    return $self->getCSourceFolder() . "/windows";
}

sub getJavaSourceFolder{
    my $self = shift;
    my $modulePath = $self->{"path"};
    return $absolutePathToRootDir . "/" . $modulePath . $self->{"name"} . "/java";
}

sub symlinkAndroidHeadersForModuleIfNeeded{
    my $self = shift;
    my $outputDir = $self->getAndroidIncludeFolder();
    my $sharedSourceFolder = $self->getSharedCSourceFolder();
    my $androidSourceFolder = $self->getAndroidCSourceFolder();
	$self->privateSymlinkHeaders($outputDir, 0, $sharedSourceFolder, $androidSourceFolder);
}

sub symlinkIOSHeadersForModuleIfNeeded{
    my $self = shift;
    my $outputDir = $self->getIOSIncludeFolder();
    my $sharedSourceFolder = $self->getSharedCSourceFolder();
    my $iOSSourceFolder = $self->getIOSCSourceFolder();
	$self->privateSymlinkHeaders($outputDir, 1, $sharedSourceFolder, $iOSSourceFolder);
}

sub symlinkWindowsHeadersForModuleIfNeeded{
    my $self = shift;
    my $outputDir = $self->getWindowsIncludeFolder();
    my $sharedSourceFolder = $self->getSharedCSourceFolder();
    my $windowsSourceFolder = $self->getWindowsCSourceFolder();
	$self->privateSymlinkHeaders($outputDir, 0, $sharedSourceFolder, $windowsSourceFolder);
}

sub privateSymlinkHeaders{
	my $self = shift;
	my $outputDir = shift;
    my $useSymlinks = shift;
	my @headerFolders = @_;
	
	if($self->{"symlink-headers"}){
        if($self->{"symlink-headers"} eq "false"){
            return;
        }
    }
    my @args = ($outputDir, $useSymlinks);
	foreach my $headerFolder (@headerFolders){
		if (-d $headerFolder ){
			push @args, $headerFolder ;
		}
	}
	if(@args > 1){
		privateExecuteCreateSymlinksForHeaders(@args);
	}
}

sub privateExecuteCreateSymlinksForHeaders{
    my @arguments = @_;
    chdir "../create-symlinks-for-headers";
    system("perl CreateSymlinksForHeaders.pl @arguments") == 0 or die "Error in create-symlinks-for-headers: $?";
    chdir $cwd;
}

1;
