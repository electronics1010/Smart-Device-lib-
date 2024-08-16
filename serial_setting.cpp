// 
// 
// 

#include "serial_setting.h"

/*
SerialTerminal setting::term;

void setting::start_setting()
{

	Serial.println("OK_start_setting");
	delay(1000);

	Serial.println(F("\nSerial terminal setting."));
	Serial.println(F("Type 'help' to display usage."));

	// Set default handler for unknown commands
	term.setDefaultHandler(unknownCommand);

	// Add command callback handlers
	term.addCommand("?", cmdHelp);
	term.addCommand("Help", cmdHelp);

	term.addCommand("MQTT_url", MQTT_url_setting);
	term.addCommand("MQTT_port", MQTT_port_setting);
	term.addCommand("MQTT_user", MQTT_user_setting);
	term.addCommand("MQTT_pass", MQTT_pass_setting);
	term.addCommand("ESP_type", ESP_type_setting);
	term.addCommand("ESP_SN", ESP_SN_setting);
	term.addCommand("DES_key", DES_key_setting);
	term.addCommand("DES_key", DES_key_setting);

	term.addCommand("End", End_setting);

	ESP.wdtDisable();

	while (true)
	{
		term.readSerial();
		delay(100);
	}

	ESP.wdtEnable(WDTO_8S);
}
void setting::unknownCommand(const char* command)
{
	// Print unknown command
	Serial.print(F("Unknown command: "));
	Serial.println(command);
}
void setting::cmdHelp()
{
	// Print usage
	Serial.println(F("Serial terminal usage:"));
	Serial.println(F("  Help or ?          Print this usage"));
	Serial.println(F("  MQTT_url           Print this usage"));
	Serial.println(F("  MQTT_port          Print this usage"));
	Serial.println(F("  MQTT_user          Print this usage"));
	Serial.println(F("  MQTT_pass          Print this usage"));
	Serial.println(F("  ESP_type           Print this usage"));
	Serial.println(F("  ESP_SN             Print this usage"));
	Serial.println(F("  DES_key            Print this usage"));
	Serial.println(F("  Save               Print this usage"));
	Serial.println(F("  End                Print decimal or hex argument"));
}
void setting::MQTT_url_setting()
{
	String data = term.getNext();
	write_String_eeprom(50, data);
	Serial.print("MQTT_url = ");
	Serial.println(data);
}
void setting::MQTT_port_setting()
{
	String data = term.getNext();
	write_String_eeprom(100, data);
	Serial.print("MQTT_port = ");
	Serial.print(data);
	Serial.println();
}
void setting::MQTT_user_setting()
{
	String data = term.getNext();
	write_String_eeprom(150, data);
	Serial.print("MQTT_user = ");
	Serial.print(data);
	Serial.println();
}
void setting::MQTT_pass_setting()
{
	String data = term.getNext();
	write_String_eeprom(200, data);
	Serial.print("MQTT_pass = ");
	Serial.print(data);
	Serial.println();
}
void setting::ESP_type_setting()
{

	String data = term.getNext();
	write_String_eeprom(250, data);
	Serial.print("ESP_type = ");
	Serial.print(data);
	Serial.println();
}
void setting::ESP_SN_setting()
{

	String data = term.getNext();
	write_String_eeprom(300, data);
	Serial.print("ESP_SN = ");
	Serial.print(data);
	Serial.println();
}
void setting::DES_key_setting()
{

	String data = term.getNext();
	write_String_eeprom(350, data);
	Serial.print("DES_key = ");
	Serial.print(data);
	Serial.println();
}
void setting::End_setting()
{
	Serial.println("end setting");
	ESP.restart();
}

void setting::write_String_eeprom(int add, String data)
{
	EEPROM.begin(512);

	int _size = data.length();
	int i;
	for (i = 0; i < _size; i++)
	{
		EEPROM.write(add + i, data[i]);
	}
	EEPROM.write(add + _size, '\0');   //Add termination null character for String Data
	EEPROM.commit();
}
String  setting::read_String_eeprom(int add)
{
	EEPROM.begin(512);
	int i;
	char data[100]; //Max 100 Bytes
	int len = 0;
	unsigned char k;
	k = EEPROM.read(add);
	while (k != '\0' && len < 500)   //Read until null character
	{
		k = EEPROM.read(add + len);
		data[len] = k;
		len++;
	}
	data[len] = '\0';
	return String(data);
}
void setting::read_setting(String& MQTT_url_, int& MQTT_port_, String& MQTT_user_, String& MQTT_pass_, String& ESP_type_, String& ESP_SN_, String& DES_key_, String& WiFi_SSID_, String& WiFi_PASS_)
{
	EEPROM.begin(512);

	MQTT_url_ = read_String_eeprom(50);
	MQTT_port_ = read_String_eeprom(100).toInt();
	MQTT_user_ = read_String_eeprom(150);
	MQTT_pass_ = read_String_eeprom(200);
	ESP_type_ = read_String_eeprom(250);
	ESP_SN_ = read_String_eeprom(300);
	DES_key_ = read_String_eeprom(350);

	WiFi_SSID_ = read_String_eeprom(400);
	WiFi_PASS_ = read_String_eeprom(450);
}


void setting::begin()
{
	EEPROM.begin(512);

	Serial.print("setting");
	for (int i = 0; i < time_setting; i++)
		if (Serial.readString() != "")
			start_setting();
		else
		{
			Serial.print(".");
			delay(1000);
		}

	Serial.println("end setting");
}

void setting::clear_eeprom()
{
	EEPROM.begin(512);

	for (int i = 0; i < 512; i++)
		EEPROM.write(i, '\0');
}

*/





















