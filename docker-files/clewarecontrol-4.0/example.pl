#! /usr/bin/perl -w

use cleware;
use Data::Dumper;

sub device_id_to_string
{
	my $device_type = $_[0];

        if ($device_type eq $cleware::POWER_DEVICE)
	{
                return "Power";
	}
        if ($device_type eq $cleware::WATCHDOGXP_DEVICE)
	{
                return "WatchdogXP";
	}
        if ($device_type eq $cleware::LED_DEVICE)
	{
                return "LED";
	}
        if ($device_type eq $cleware::WATCHDOG_DEVICE)
	{
                return "Watchdog";
	}
        if ($device_type eq $cleware::AUTORESET_DEVICE)
	{
                return "Autoreset device";
	}
        if ($device_type eq $cleware::SWITCH1_DEVICE)
	{
                return "Switch1";
	}
        if ($device_type eq $cleware::SWITCH2_DEVICE)
	{
                return "Switch2";
	}
        if ($device_type eq $cleware::SWITCH3_DEVICE)
	{
                return "Switch3";
	}
        if ($device_type eq $cleware::SWITCH4_DEVICE)
	{
                return "Switch4";
	}
        if ($device_type eq $cleware::SWITCH5_DEVICE)
	{
                return "Switch5";
	}
        if ($device_type eq $cleware::SWITCH6_DEVICE)
	{
                return "Switch6";
	}
        if ($device_type eq $cleware::SWITCH7_DEVICE)
	{
                return "Switch7";
	}
        if ($device_type eq $cleware::SWITCH8_DEVICE)
	{
                return "Switch8";
	}
        if ($device_type eq $cleware::SWITCHX_DEVICE)
	{
                return "SwitchX";
	}
        if ($device_type eq $cleware::TEMPERATURE_DEVICE)
	{
                return "Temperature sensor";
	}
        if ($device_type eq $cleware::TEMPERATURE2_DEVICE)
	{
                return "Temperature 2 sensor";
	}
        if ($device_type eq $cleware::TEMPERATURE5_DEVICE)
	{
                return "Temperature 5 sensor";
	}
        if ($device_type eq $cleware::HUMIDITY1_DEVICE)
	{
                return "Humidity sensor";
	}
        if ($device_type eq $cleware::CONTACT00_DEVICE)
	{
                return "Contact 00 device";
	}
        if ($device_type eq $cleware::CONTACT01_DEVICE)
	{
                return "Contact 01 device";
	}
        if ($device_type eq $cleware::CONTACT02_DEVICE)
	{
                return "Contact 02 device";
	}
        if ($device_type eq $cleware::CONTACT03_DEVICE)
	{
                return "Contact 03 device";
	}
        if ($device_type eq $cleware::CONTACT04_DEVICE)
	{
                return "Contact 04 device";
	}
        if ($device_type eq $cleware::CONTACT05_DEVICE)
	{
                return "Contact 05 device";
	}
        if ($device_type eq $cleware::CONTACT06_DEVICE)
	{
                return "Contact 06 device";
	}
        if ($device_type eq $cleware::CONTACT07_DEVICE)
	{
                return "Contact 07 device";
	}
        if ($device_type eq $cleware::CONTACT08_DEVICE)
	{
                return "Contact 08 device";
	}
        if ($device_type eq $cleware::CONTACT09_DEVICE)
	{
                return "Contact 09 device";
	}
        if ($device_type eq $cleware::CONTACT10_DEVICE)
	{
                return "Contact 10 device";
	}
        if ($device_type eq $cleware::CONTACT11_DEVICE)
	{
                return "Contact 11 device";
	}
        if ($device_type eq $cleware::CONTACT12_DEVICE)
	{
                return "Contact 12 device";
	}
        if ($device_type eq $cleware::CONTACT13_DEVICE)
	{
                return "Contact 13 device";
	}
        if ($device_type eq $cleware::CONTACT14_DEVICE)
	{
                return "Contact 14 device";
	}
        if ($device_type eq $cleware::CONTACT15_DEVICE)
	{
                return "Contact 15 device";
	}
        if ($device_type eq $cleware::ENCODER01_DEVICE)
	{
                return "Encoder 01 device";
	}
        if ($device_type eq $cleware::F4_DEVICE)
	{
                return "F4 device";
	}
        if ($device_type eq $cleware::KEYC01_DEVICE)
	{
                return "Keyc01 device";
	}
        if ($device_type eq $cleware::KEYC16_DEVICE)
	{
                return "Keyc16 device";
	}
        if ($device_type eq $cleware::ADC0800_DEVICE)
	{
                return "AC0800 device";
	}
        if ($device_type eq $cleware::ADC0801_DEVICE)
	{
                return "AC0801 device";
	}
        if ($device_type eq $cleware::ADC0802_DEVICE)
	{
                return "AC0802 device";
	}
        if ($device_type eq $cleware::ADC0803_DEVICE)
	{
                return "AC0803 device";
	}
        if ($device_type eq $cleware::COUNTER00_DEVICE)
	{
                return "Counter device";
	}
        if ($device_type eq $cleware::BUTTON_NODEVICE)
	{
                return "Button no device";
	}

	return "device type not recognized!"
}

$c = cleware::CUSBaccess->new();

$n_devices = cleware::CUSBaccess::OpenCleware($c);

print "Number of devices: $n_devices\n";

my $i;
for($i=0; $i<$n_devices; $i++)
{
        my $devType = cleware::CUSBaccess::GetUSBType($c, $i);
        my $devTypeStr = device_id_to_string($devType);
        my $version = cleware::CUSBaccess::GetVersion($c, $i);
        my $serial = cleware::CUSBaccess::GetSerialNumber($c, $i);

        print "device: $i, type: $devTypeStr ($devType), version: $version, serial number: $serial\n";

        # these two are not neccessary normally for reading temperatures
        # they're here as an example
        # rc is 0 for failure, 1 for ok
	my $rc;
        $rc = cleware::CUSBaccess::ResetDevice($c, $i);
        $rc = cleware::CUSBaccess::StartDevice($c, $i);

	if ($devType eq $cleware::TEMPERATURE_DEVICE || $devType eq $cleware::TEMPERATURE2_DEVICE || $devType eq $cleware::TEMPERATURE5_DEVICE)
	{
		my $temperature = cleware::CUSBaccess::GetTemperatureSimple($c, $i);

		print "\tcurrent temperature: $temperature\n";
	}

	if ($devType eq $cleware::HUMIDITY1_DEVICE)
	{
		my $humidity = cleware::CUSBaccess::GetHumiditySimple($c, $i);

		print "\tcurrent humidity: $humidity\n";
	}

	# Note: the "ampel" (traffic light) is also a switch device, with actually 3 switches (one per light)
	if ($devType eq $cleware::SWITCH1_DEVICE || $devType eq $cleware::SWITCH2_DEVICE || $devType eq $cleware::SWITCH3_DEVICE || $devType eq $cleware::SWITCH4_DEVICE || $devType eq $cleware::SWITCH5_DEVICE || $devType eq $cleware::SWITCH6_DEVICE || $devType eq $cleware::SWITCH7_DEVICE || $devType eq $cleware::SWITCH8_DEVICE || $devType eq $cleware::SWITCHX_DEVICE)
	{
		my $switch_nr = 0; # 0...15
		my $state = cleware::CUSBaccess::GetSwitch($c, $i, 16 + $switch_nr);
		print "\tswitch $switch_nr state: $state\n";

		my $new_state = 1; # 0 or 1
		$rc = cleware::CUSBaccess::SetSwitch($c, $i, 16 + $switch_nr, $new_state);
	}

	if ($devType eq $cleware::CUSBaccess::LED_DEVICE)
	{
		my $led = $cleware::CUSBaccess::LED_0; # 0...3
		my $value = 10; # 0...15
		$rc = cleware::CUSBaccess::SetLED($c, $i, $led, $value);
	}

	if ($devType eq $cleware::ADC0800_DEVICE || $devType eq $cleware::ADC0801_DEVICE || $devType eq $cleware::ADC0802_DEVICE || $devType eq $cleware::ADC0803_DEVICE)
	{
		my $channel = 1; # 0 or 1
		$rc = cleware::CUSBaccess::SelectADCChannel($c, $i, $channel);

		my $scale = 0; # 0...2 for 5, 13 or 24V
		my $voltage = cleware::CUSBaccess::GetADCValue($c, $i, $scale);
		print "\tmeasured voltage: $voltage\n";
	}
}
