// Basic class definitions for access to USB HID devices
//
// (C) 2001 Copyright Cleware GmbH
// All rights reserved
//
// History:
// 05.01.01	ws	Initial coding
// 17.07.01	ws	cleanup interface
// 03.11.02	ws	small changes for Linux


#ifndef __USBACCESSBASIC_H__
#define __USBACCESSBASIC_H__

#include <hidapi/hidapi.h>

typedef hid_device * HANDLE;

enum USBtype_enum {	ILLEGAL_DEVICE=0,
						LED_DEVICE=0x01,
						POWER_DEVICE=0x02,
						DISPLAY_DEVICE=0x03,
						WATCHDOG_DEVICE=0x05,
						AUTORESET_DEVICE=0x06,
						WATCHDOGXP_DEVICE=0x07,
						SWITCH1_DEVICE=0x08,
						SWITCH2_DEVICE=0x09, SWITCH3_DEVICE=0x0a, SWITCH4_DEVICE=0x0b,
						SWITCH5_DEVICE=0x0c, SWITCH6_DEVICE=0x0d, SWITCH7_DEVICE=0x0e, SWITCH8_DEVICE=0x0f,
						TEMPERATURE_DEVICE=0x10,
						TEMPERATURE2_DEVICE=0x11,
						TEMPERATURE5_DEVICE=0x15, 
						HUMIDITY1_DEVICE=0x20,HUMIDITY2_DEVICE=0x21,
						SWITCHX_DEVICE=0x28,		// new switch 3,4,8
						// CONTACT1_DEVICE=0x30 
						CONTACT00_DEVICE=0x30, CONTACT01_DEVICE=0x31, CONTACT02_DEVICE=0x32, CONTACT03_DEVICE=0x33, 
						CONTACT04_DEVICE=0x34, CONTACT05_DEVICE=0x35, CONTACT06_DEVICE=0x36, CONTACT07_DEVICE=0x37, 
						CONTACT08_DEVICE=0x38, CONTACT09_DEVICE=0x39, CONTACT10_DEVICE=0x3a, CONTACT11_DEVICE=0x3b, 
						CONTACT12_DEVICE=0x3c, CONTACT13_DEVICE=0x3d, CONTACT14_DEVICE=0x3e, CONTACT15_DEVICE=0x3f, 
						F4_DEVICE=0x40, 
						KEYC01_DEVICE=0x41, KEYC16_DEVICE=0x42,MOUSE_DEVICE=0x43,
						ADC0800_DEVICE=0x50, ADC0801_DEVICE=0x51, ADC0802_DEVICE=0x52, ADC0803_DEVICE=0x53, 
						COUNTER00_DEVICE=0x60, 
						ENCODER01_DEVICE=0x80,
						BUTTON_NODEVICE=0x1000
						} ;
enum USBactions {		LEDs=0, EEwrite=1, EEread=2, Reset=3, KeepCalm=4, GetInfo=5, 
						StartMeasuring=6,		// USB-Humidity
						Configure=7,			// USB-IO16-V10, USB-Counter-V05
						Display=8,				// USB/Display
						RunPoint=10,			// USB-Encoder
						Programm=15				// Transfer new Firmware (internal use only)
						} ;

typedef struct {
	unsigned short v, p;
	hid_device *handle;
	int	gadgetVersionNo;
	enum USBtype_enum	gadgettype;
	int	SerialNumber;
	int	report_type;
	int	HWversion ;
	} SUSBdata;

extern int nr;

void cwInitCleware();
int	cwOpenCleware(const char *path);	// returns number of found Cleware devices
int cwRecover(int devNo);
void cwCloseCleware();
int	cwGetValue(int deviceNo, unsigned char *buf, int bufsize);
int	cwSetValue(int deviceNo, unsigned char *buf, int bufsize);
hid_device * cwGetHandle(int deviceNo);
int	cwGetVersion(int deviceNo);
int	cwGetSerialNumber(int deviceNo);
enum USBtype_enum	cwGetUSBType(int deviceNo);
int							cwValidSerNum(int SerialNumber, enum USBtype_enum devType) ;
void						cwDebugWrite(char *s) ;
void						cwDebugClose() ;
int cwGetHWversion(int deviceNo);
int							cwIOX(int deviceNo, int addr, int data) ;

#endif // __USBACCESS_H__
