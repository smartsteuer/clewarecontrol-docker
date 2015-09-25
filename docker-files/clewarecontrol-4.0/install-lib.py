#! /usr/bin/python

import sys
import shutil

found=0
for p in sys.path:
	pos = p.find('/local/', 0)
	if pos >= 0:
		found=1
		print 'Installing into %s' % (p)
		shutil.copy('_cleware.so', p)
		shutil.copy('cleware.py', p)

if found == 0:
	print 'Could not find a location to copy the library into.'
	print 'You may want to install cleware.py and _cleware.so into the appropriate directory.'
else:
	print 'Finished.'
