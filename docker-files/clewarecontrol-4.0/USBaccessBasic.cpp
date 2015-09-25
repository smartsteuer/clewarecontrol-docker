// Basic class implementation for access to USB HID devices
//
// (C) 2001 Copyright Cleware GmbH
// All rights reserved
//
// History:
// 05.01.01	ws	Initial coding
// 01.11.01	ws	Linux coding
// 30.10.12	fvh	libusb version

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "USBaccessBasic.h"

#define TIMEOUT 1000

const int maxHID = 128 ;
SUSBdata data[128] ;

int nr = 0;

void cwInitCleware()
{
	hid_init();
}

void cwCloseCleware()
{
	for(int h=0; h < maxHID; h++)
	{
		if (data[h].handle)
		{
			hid_close(data[h].handle);

			data[h].handle = NULL;
		}
	}

	hid_exit();
}

int	
cwIOX(int deviceNo, int addr, int datum) {	// return datum if ok, datum=-1=Read operation
	const int maxbufsize = 8 ;
	int bufsize = 6 ;
	unsigned char buf[maxbufsize] ;
	int ok = 1 ;
	if (deviceNo < 0 || deviceNo >= maxHID || data[deviceNo].handle == NULL)
		return-1 ;

	int devType = data[deviceNo].gadgettype ;
	int version = data[deviceNo].gadgetVersionNo ;
	int sixteenbit = (devType == TEMPERATURE2_DEVICE || devType == HUMIDITY1_DEVICE || devType == HUMIDITY2_DEVICE) ;


	if (datum >= 0) {		// -1 = Read command
		buf[0] = EEwrite ;
		if (sixteenbit) {
			buf[1] = addr >> 8 ;	// high byte 0
			buf[2] = addr ;
			buf[3] = datum ;
			cwSetValue(deviceNo, buf, 4) ;
			}
		else if (devType == CONTACT00_DEVICE && version > 6) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 5) ;
			}
		else if (devType == DISPLAY_DEVICE) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 5) ;
			}
		else if (devType == WATCHDOGXP_DEVICE || devType == SWITCHX_DEVICE) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 5) ;
			}
		else if (devType == ENCODER01_DEVICE) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 6) ;
			}
		else if (devType == ADC0800_DEVICE) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 3) ;
			}
		else if (devType == POWER_DEVICE) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 3) ;
			}
		else if (devType == KEYC16_DEVICE || devType == KEYC01_DEVICE) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 5) ;
			}
		else if (devType == MOUSE_DEVICE) {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 5) ;
			}
		else {
			buf[1] = addr ;
			buf[2] = datum ;
			cwSetValue(deviceNo, buf, 3) ;
			}
		usleep(100*1000) ;
		}

	buf[0] = EEread ;
	if (sixteenbit) {
		buf[1] = 0 ;	// high byte 0
		buf[2] = addr ;
		buf[3] = 0 ;
		cwSetValue(deviceNo, buf, 4) ;
		bufsize = 7 ;
		}
	else if (devType == CONTACT00_DEVICE && version > 6) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 5) ;
		}
	else if (devType == DISPLAY_DEVICE) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 5) ;
		}
	else if (devType == WATCHDOGXP_DEVICE || devType == SWITCHX_DEVICE) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 5) ;
		}
	else if (devType == KEYC16_DEVICE || devType == KEYC01_DEVICE) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 5) ;
		bufsize = 8 ;
		}
	else if (devType == MOUSE_DEVICE) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 5) ;
		bufsize = 4 ;
		}
	else if (devType == ADC0800_DEVICE) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 3) ;
		bufsize = 4 ;
		}
	else if (devType == POWER_DEVICE) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 3) ;
		bufsize = 3 ;
		}
	else if (devType == ENCODER01_DEVICE) {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 6) ;
		}
	else {
		buf[1] = addr ;
		buf[2] = 0 ;
		cwSetValue(deviceNo, buf, 3) ;
		}

	usleep(10*1000) ;
	ok = 40 ;
	int Xdata = -1 ;
	while (ok) {
		if (cwGetValue(deviceNo, buf, bufsize)) {
			if ((buf[0] & 0x80) == 0) {
				if (--ok == 0) {
					// MessageBox("GetValue still not valid", "Error") ;
					break ;
					}
				else {
					usleep(10*1000) ;
					continue ;
					}
				}
			int Xaddr = 0 ;
			if (bufsize == 3 || devType == MOUSE_DEVICE) {
				Xaddr = buf[1] ;
				Xdata = buf[2] ;
				}
			else if (bufsize == 4) {
				Xaddr = buf[2] ;
				Xdata = buf[3] ;
				}
			else {
				Xaddr = buf[4] ;
				Xdata = buf[5] ;
				}
			if (sixteenbit) {
				Xaddr = (Xaddr << 8) + buf[5] ;
				Xdata = buf[6] ;
				}
			if (Xaddr != addr) {
				if (--ok == 0) {
					// MessageBox("GetValue address error", "Error") ;
					break ;
					}
				else {
					usleep(10*1000) ;
					continue ;
					}
				}
			if (datum >= 0 && Xdata != datum) {
				if (--ok == 0) {
					// MessageBox("Write error", "Error") ;
					break ;
					}
				else {
					usleep(10*1000) ;
					continue ;
					}
				}
			break ;
			}
		else {
			if (--ok == 0) {
				// MessageBox("GetValue failed", "Error") ;
				break ;
				}
			else {
				usleep(10*1000) ;
				continue ;
				}
			}
		break ;		// read was ok
		}
	if (!ok)
		Xdata = -1 ;

	return Xdata ;
	}

// returns number of found Cleware devices
int cwOpenCleware(const char *path = NULL)
{
	int n = 0;
	struct hid_device_info *devs = NULL, *cur_dev = NULL;

	memset(&data, 0x00, sizeof data);

	cur_dev = devs = hid_enumerate(0x0d50, 0x0);

	while (cur_dev)
	{
		data[n].v = cur_dev->vendor_id;
		data[n].p = cur_dev->product_id;

		data[n].gadgettype = (enum USBtype_enum)data[n].p;
		data[n].gadgetVersionNo = cur_dev -> release_number;

                char buffer[256] = { 0 };
                wcstombs(buffer, cur_dev->serial_number, wcslen(cur_dev->serial_number));

                data[n].SerialNumber = strtol(buffer, NULL, 16);
		data[n].report_type = 123; // HID_REPORT_ID_FIRST; // NOT USED *FVH*
		if (data[n].SerialNumber == 0x63813) {	// this is the next controller - get serial number directly
			data[n].HWversion = 13 ;
			data[n].SerialNumber = -1 ;
		}
		if (data[n].SerialNumber <= 0) {		// getting the Serial number failed, so get it directly!
			data[n].handle = hid_open(data[n].v, data[n].p, NULL);
			int SerNum = 0 ;
			int addr = 0;
			for (addr=8 ; addr <= 14 ; addr++) {	// unicode byte 2 == 0
				int data = cwIOX(n, addr, -1) ;
				if (data >= '0' && data <= '9')
					SerNum = SerNum * 16 + data - '0' ;
				else if (data >= 'A' && data <= 'F')
					SerNum = SerNum * 16 + data - 'A' + 10 ;
				else {
					SerNum = -1 ;		// failed!
					break ;
				}
			}
			data[n].SerialNumber = SerNum ;
			hid_close(data[n].handle);
			data[n].handle = NULL;
		}

		n++;
		cur_dev = cur_dev->next;
	}

	hid_free_enumeration(devs);

	return n;
}

int cwOpenDevice(int index)
{
	if (data[index].handle)
		return 1;

	data[index].handle = hid_open(data[index].v, data[index].p, NULL);

	char ok = data[index].handle != NULL;

	if (!ok)
		fprintf(stderr, "Failed to open %04x:%04x (%d)\n", data[index].v, data[index].p, data[index].SerialNumber);

	return ok;
}

int cwCloseDevice(int index)
{
	if (data[index].handle)
	{
		hid_close(data[index].handle);

		data[index].handle = NULL;
	}

	return 1;
}

int cwRecover(int devNo)
{
	if (data[devNo].handle == NULL)
		return 0;

	return 1;
}

void fail(const char *msg, hid_device *handle)
{
	const wchar_t *wstr = hid_error(handle);

	if (!wstr)
	{
		if (errno)
			printf("%s: %s\n", msg, strerror(errno));
		else
			printf("%s\n", msg);
	}
	else
	{
		int len = wcslen(wstr);
		char* ascii = new char[len + 1];

		wcstombs(ascii, wstr, len);

		printf("%s: %s\n", msg, ascii);

		delete [] ascii;
	}
}

int cwGetValue(int deviceNo, unsigned char *buf, int bufsize)
{
	if (!cwOpenDevice(deviceNo))
		return 0;

	if (data[deviceNo].handle == NULL)
		return 0;

	unsigned char lbuf[3] = { 0x00, (unsigned char)(nr++), 0x81 };
	if (hid_send_feature_report(data[deviceNo].handle, lbuf, sizeof lbuf) < 0)
	{
		fail("cwGetValue::hid_write() failed", data[deviceNo].handle);

                return 0;
        }

	if (hid_read(data[deviceNo].handle, buf, bufsize) < 0)
	{
		fail("cwGetValue::hid_read() failed", data[deviceNo].handle);

                return 0;
        }

	return 1;
}

int cwSetValue(int deviceNo, unsigned char *buf, int bufsize)
{
	if (!cwOpenDevice(deviceNo))
		return 0;

	if (data[deviceNo].handle == NULL)
		return 0;

	char *b = new char[bufsize + 1];
	memcpy(b + 1, buf, bufsize);
	b[0] = 0x00;

//#ifdef macos
#if 1
	if (hid_write(data[deviceNo].handle, (unsigned char *)b, bufsize + 1) < 0)
#else
	if (hid_send_feature_report(data[deviceNo].handle, (unsigned char *)b, bufsize + 1) < 0)
#endif
	{
		fail("cwSetValue::hid_write() failed", data[deviceNo].handle);

		delete [] b;

                return 0;
        }

	delete [] b;

	return 1;
}

hid_device * cwGetHandle(int deviceNo)
{ 
	if (!cwOpenDevice(deviceNo))
		return 0;

	return data[deviceNo].handle;
}

int cwGetVersion(int deviceNo)
{
	return data[deviceNo].gadgetVersionNo;
}

int cwGetSerialNumber(int deviceNo)
{ 
	return data[deviceNo].SerialNumber;
}

enum USBtype_enum cwGetUSBType(int deviceNo)
{ 
	return data[deviceNo].gadgettype;
}

int
cwValidSerNum(int SerialNumber, enum USBtype_enum devType) {
	static int outdated[] = {
		54,59,60,62,63,64,65,66,67,68,69,
		72,74,75,76,77,82,83,85,87,88,89,
		90,91,92,93,95,96,98,99,
		100,101,102,103,105,106,107,108,109,110,
		113,116,117,119,120,122,124,125,126,128,
		131,132,135,139,140,142,143,145,147,148,149,
		150,151,152,153,154,155,156,157,160,161,162,163,168,169,
		170,171,172,173,174,175,176,180,184,187,188,189,190,191,192,193,195,197,198,
		201,203,204, 205, 206, 219,220,221,260,272,273,274,275,276,278,279,
		280,281,416,
		5002,5003,5004,5005,5006,5007,5008,5010,
		5011,5012,5013,5014,5015,5016,
		5017,5018,5019,5020,5021,5022,5023,5024,
		5025,5026,5028,5029,5032,5033,5034,
		5035,5036,5041,5043,5044,5046,5049,5050,
		5052,5053,5055,5057,5071,5073,5076,5089,5091,5101,5102,5103,
		5104,5106,5109,5114,5116,5117,5118,5119,
		5120,5121,5122,5147,5163,5164,7502,7503,
		7504,7505,7511,7513,8192,8193,8194,
		8503,8504,8505,8506,8507,8508,8509,8510,8511,8512,8513
		} ;

	static int outdatedSwitches[] = {		// double numbers!!
		510,511,513,514,517,518,520,532			//	Switches
//		, 5314	// test
		} ;

	int rval = 1 ;

	int size = sizeof(outdated) / sizeof(int) ;
	int *pt = &(outdated[0]) ;
	int i ;

	for (i=0 ; i < size ; i++, pt++) {
		if (SerialNumber == *pt) {
			rval = 0 ;
			break ;
			}
		}
	if (rval == 1 && devType == SWITCH1_DEVICE) {
		size = sizeof(outdatedSwitches) / sizeof(int) ;
		pt = &(outdatedSwitches[0]) ;
		for (i=0 ; i < size ; i++, pt++) {
			if (SerialNumber == *pt) {
				rval = 0 ;
				break ;
				}
			}
		}

	return rval ; 
	}

void
cwDebugWrite(char *s) { 
	fputs(s, stderr) ;
	}

void
cwDebugClose() { 
	}

int
cwGetHWversion(int deviceNo) {                  // return current
        int rval = 0 ;

        if (deviceNo < 0 || deviceNo >= maxHID || data[deviceNo].handle == NULL)
                rval = -1 ;
        else
                rval = data[deviceNo].HWversion ;

        return rval ;
        }
