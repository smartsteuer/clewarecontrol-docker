#! /usr/bin/perl -w

use File::Copy;
use File::Path qw(make_path);

foreach(@INC)
{
	if (/\/local\//)
	{
		print "Installing in $_...\n";

		make_path($_);

		copy('cleware.pm', $_);
		copy('cleware.so', $_);

		last;
	}
}
