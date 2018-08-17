
package Constants;

use warnings;
use strict;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw($sharedSourceFolder @possibleSourceFolderNames);

our $sharedSourceFolder = "shared";
our @possibleSourceFolderNames = ("android", "ios", "windows");

1;
