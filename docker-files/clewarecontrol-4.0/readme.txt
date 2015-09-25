build instructions
------------------
Required libraries:
	libhidapi-dev

Since version 4.0 clewarecontrol uses this library to abstract the
interfacing with the kernel. That way it may work on other OSes and new(er)
kernel as well.

Installation:
	make install


usage
-----
Please see the man-page for help on how to use it:
	make clewarecontrol

or run the program with the -h switch:
	clewarecontrol -h

Please also check the website for tips and help.


devices
-------
- temperature sensor
	clewarecontrol -rt

- humidity sensor
  This device needs to be "started" first, then you can read sensor readings
	clewarecontrol -ag -rh

- 2 channel AD converter (analog to digital)
  First you need to know what it range it works: 5v, 13v or 24v
  then you must select the channel to read from - the device has 2 channels
  after selecting the channel, you can keep reading
	clewarecontrol -ai x        where x is 0 or 1 (selects channel)
	clewarecontrol -ra y        where y is 0 voor 5v, 1 for 13v, etc.
 
- Ampel ("Switch1 (8)")
  The traffic light is, from clewarecontrol seen, a device with 3 switches in
  it that can be individiually switched on and off
	clewarecontrol -as x y      where x is 0, 1 or 2 (0=red, 2=green) and
                                    y is 0 or 1 (0 is off)

- IO16 ("Contact 00 device (48)")
  The IO16 is a 16 port I/O interface. You can configure each pin to be either
  input or output. This setting is stored in an eprom so that a pin cannot
  become accidently output while you expected an input.
  Set the direction with:
	clewarecontrol -ad x        where x is a hex value representing a 1
                                    or 0 selecting the direction
  After that you can set the output pins to 1 or 0 with:
	clewarecontrol -am x        where is a hex value

- Luminus
  This is in fact an AD converter with integrated hardware which measures the
  amount of light. It has 1 chnanel, so you don't need to select it (like the
  generic ADC). Reading values (in version 2.5) can be perfomed like his:
	clewarecontrol -ra 0
  This gives a value between 0 and 5. I (developer of this Linux program)
  need to buy a lux meter to scale this correctly.


- USB-cutter
  This is a device which is at its heart a switch like the other switches.
  To use it, you need to start it:
	clewarecontrol -ag
  then, you can toggle the USB status like this:
	clewarecontrol -as 0 1      this will "cut" the USB device (switching
	                            it off)
	clewarecontrol -as 0 0      this will enable the USB device again(!)
  indeed, the logic is inverted.


-mintrig / -maxtrig
-------------------
Run the program with -c 0 so that it keeps running forever (unless you want to
have it monitor the value for a shorter time).
Also start it with -F so that it runs in the background.
Then set the -mintrig or -maxtrig switches.
As the last parameter, set the sensor to monitor: -rh (humidity), -rt
(temperature), etc.
For example:
	clewarecontrol -c 0 -maxtrig 0.5 ./myscript.sh -ra 0
If the ADC tells us that the voltage is over 0.5 volts, then "myscript.sh" is
invoked. As a parameter, the script will get the measured value.


I would be delighted if you share your experiences with me!


python library
--------------
please see readme-python.txt for details on how to create and use the python
library.


perl library
--------------
please see readme-perl.txt for details on how to create and use the perl
library.


problems
--------
If you encounter any problems when using clewarecontrol with Cleware devices,
DO NOT contact Cleware but please contact me: folkert@vanheusden.com

Of course you can always write me when you have questions/suggestions/etc.
 folkert@vanheusden.com


FAQ
---
Q1. Values retrieved are invalid
A1. Occasionally the values retrieved are invalid. E.g. a temperature of 170
    degrees and such. In that case you can reset the device (might need to
    reset it multiple times!) and then it'll work

Q2. It does not compile on SuSE Enterprise Linux 10
A2. Insert in file USBaccessBasic.c at line 17 (that is BEFORE the line
    including usbdevice_fs.h!) the following line:
	#define __user

Q3. clewarecontrol -l doesn't list any devices
A3. The Cleware USB library expects the following files to exist:
	crw-rw-rw- 1 root root 180,  96 May  9  2005 /dev/usb/hiddev0
	crw-rw-rw- 1 root root 180,  97 May  9  2005 /dev/usb/hiddev1
	...
	crw-rw-rw- 1 root root 180, 110 May  9  2005 /dev/usb/hiddev14
	crw-rw-rw- 1 root root 180, 111 May  9  2005 /dev/usb/hiddev15

    Since version 1.2 you can use -p to select a different path, eg.:
	clewarecontrol -p /dev -l

    Make sure the user you're running clewarecontrol from has enought rights
    to access the devices. For starters, to see if it works at all, run it as
    root.

Q4. clewarecontrol still can't find any devices
A4. If that still does not give any output then please e-mail me the output of
    the following commands:
	uname -a
	lsusb
	lsmod
	strace clewarecontrol -l
	ps -deaf | grep udev
	find /dev -name hiddev\*

    Please also tell me what distribution (e.g. redhat/suse/ubuntu) and what
    version you're using


Regards,

Folkert van Heusden
