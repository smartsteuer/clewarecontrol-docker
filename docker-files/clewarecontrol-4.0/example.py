#! /usr/bin/python

import cleware

def device_id_to_string(device_type):
        if device_type == cleware.POWER_DEVICE:
                return "Power"
        if device_type == cleware.WATCHDOGXP_DEVICE:
                return "WatchdogXP"
        if device_type == cleware.LED_DEVICE:
                return "LED"
        if device_type == cleware.WATCHDOG_DEVICE:
                return "Watchdog"
        if device_type == cleware.AUTORESET_DEVICE:
                return "Autoreset device"
        if device_type == cleware.SWITCH1_DEVICE:
                return "Switch1"
        if device_type == cleware.SWITCH2_DEVICE:
                return "Switch2"
        if device_type == cleware.SWITCH3_DEVICE:
                return "Switch3"
        if device_type == cleware.SWITCH4_DEVICE:
                return "Switch4"
        if device_type == cleware.SWITCH5_DEVICE:
                return "Switch5"
        if device_type == cleware.SWITCH6_DEVICE:
                return "Switch6"
        if device_type == cleware.SWITCH7_DEVICE:
                return "Switch7"
        if device_type == cleware.SWITCH8_DEVICE:
                return "Switch8"
        if device_type == cleware.SWITCHX_DEVICE:
                return "SwitchX"
        if device_type == cleware.TEMPERATURE_DEVICE:
                return "Temperature sensor"
        if device_type == cleware.TEMPERATURE2_DEVICE:
                return "Temperature 2 sensor"
        if device_type == cleware.TEMPERATURE5_DEVICE:
                return "Temperature 5 sensor"
        if device_type == cleware.HUMIDITY1_DEVICE:
                return "Humidity sensor"
        if device_type == cleware.CONTACT00_DEVICE:
                return "Contact 00 device"
        if device_type == cleware.CONTACT01_DEVICE:
                return "Contact 01 device"
        if device_type == cleware.CONTACT02_DEVICE:
                return "Contact 02 device"
        if device_type == cleware.CONTACT03_DEVICE:
                return "Contact 03 device"
        if device_type == cleware.CONTACT04_DEVICE:
                return "Contact 04 device"
        if device_type == cleware.CONTACT05_DEVICE:
                return "Contact 05 device"
        if device_type == cleware.CONTACT06_DEVICE:
                return "Contact 06 device"
        if device_type == cleware.CONTACT07_DEVICE:
                return "Contact 07 device"
        if device_type == cleware.CONTACT08_DEVICE:
                return "Contact 08 device"
        if device_type == cleware.CONTACT09_DEVICE:
                return "Contact 09 device"
        if device_type == cleware.CONTACT10_DEVICE:
                return "Contact 10 device"
        if device_type == cleware.CONTACT11_DEVICE:
                return "Contact 11 device"
        if device_type == cleware.CONTACT12_DEVICE:
                return "Contact 12 device"
        if device_type == cleware.CONTACT13_DEVICE:
                return "Contact 13 device"
        if device_type == cleware.CONTACT14_DEVICE:
                return "Contact 14 device"
        if device_type == cleware.CONTACT15_DEVICE:
                return "Contact 15 device"
        if device_type == cleware.ENCODER01_DEVICE:
                return "Encoder 01 device"
        if device_type == cleware.F4_DEVICE:
                return "F4 device"
        if device_type == cleware.KEYC01_DEVICE:
                return "Keyc01 device"
        if device_type == cleware.KEYC16_DEVICE:
                return "Keyc16 device"
        if device_type == cleware.ADC0800_DEVICE:
                return "AC0800 device"
        if device_type == cleware.ADC0801_DEVICE:
                return "AC0801 device"
        if device_type == cleware.ADC0802_DEVICE:
                return "AC0802 device"
        if device_type == cleware.ADC0803_DEVICE:
                return "AC0803 device"
        if device_type == cleware.COUNTER00_DEVICE:
                return "Counter device"
        if device_type == cleware.BUTTON_NODEVICE:
                return "Button no device"

	return "device type not recognized!"


c = cleware.CUSBaccess()

n_devices = c.OpenCleware()

print "Number of devices: %d" % (n_devices)

for i in range(n_devices):
	devType = c.GetUSBType(i);
	devTypeStr = device_id_to_string(devType)
	version = c.GetVersion(i)
	serial = c.GetSerialNumber(i)

	print "device: %d, type: %s (%d), version: %d, serial number: %d" % (i, devTypeStr, devType, version, serial)

	# these two are not neccessary normally for reading temperatures
	# they're here as an example
	# rc is 0 for failure, 1 for ok
	rc = c.ResetDevice(i);
	rc = c.StartDevice(i);

	if devType == cleware.TEMPERATURE_DEVICE or devType == cleware.TEMPERATURE2_DEVICE or devType == cleware.TEMPERATURE5_DEVICE:
		temperature = c.GetTemperatureSimple(i)

		print "\tcurrent temperature: %f" % (temperature)

	if devType == cleware.HUMIDITY1_DEVICE:
		humidity = c.GetHumiditySimple(i)

		print "\tcurrent humidity: %f" % (humidity)

	# Note: the "ampel" (traffic light) is also a switch device, with actually 3 switches (one per light)
	if devType == cleware.SWITCH1_DEVICE or devType == cleware.SWITCH2_DEVICE or devType == cleware.SWITCH3_DEVICE or devType == cleware.SWITCH4_DEVICE or devType == cleware.SWITCH5_DEVICE or devType == cleware.SWITCH6_DEVICE or devType == cleware.SWITCH7_DEVICE or devType == cleware.SWITCH8_DEVICE or devType == cleware.SWITCHX_DEVICE:

		switch_nr = 0 # 0...15
		state = c.GetSwitch(i, 16 + switch_nr)
		print "\tswitch %d state: %d" % (switch_nr, state)

		new_state = 1 # 0 or 1
		rc = c.SetSwitch(i, 16 + switch_nr, new_state)

	if devType == c.LED_DEVICE:
		led = 1 # 0...3
		value = 10 # 0...15
		rc = c.SetLED(i, led, value)

	if devType == c.ADC0800_DEVICE or devType == c.ADC0801_DEVICE or devType == c.ADC0802_DEVICE or devType == c.ADC0803_DEVICE:
		channel = 1 # 0 or 1
		rc = c.SelectADCChannel(i, channel)

		scale = 0 # 0...2 for 5, 13 or 24V
		voltage = c.GetADCValue(i, scale)
		print "\tmeasured voltage: %f" % (voltage)
