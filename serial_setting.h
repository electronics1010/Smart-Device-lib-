
#ifndef _SERIAL_SETTING_h
#define _SERIAL_SETTING_h

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <EEPROM.h>
#include <List.hpp>
#include <StringSplitter.h>
/*
class setting
{
public:
	setting()
	{
		EEPROM.begin(512);
		term = SerialTerminal(newlineChar_setting, delimiterChar_setting);
	}
	void begin();
	void clear_eeprom();
	void read_setting(String& MQTT_url_, int& MQTT_port_, String& MQTT_user_, String& MQTT_pass_, String& ESP_type_, String& ESP_SN_, String& DES_key_, String& WiFi_SSID_, String& WiFi_PASS_);

private:
	void start_setting();
	static void unknownCommand(const char* command);
	static void cmdHelp();
	static void MQTT_url_setting();
	static void MQTT_port_setting();
	static void MQTT_user_setting();
	static void MQTT_pass_setting();
	static void ESP_type_setting();
	static void ESP_SN_setting();
	static void DES_key_setting();
	static void End_setting();

	static void write_String_eeprom(int add, String data);

	char newlineChar_setting = '\n';
	char delimiterChar_setting = ' ';
	int is_setting = 1;
	int time_setting = 10;
	static SerialTerminal term;



	String read_String_eeprom(int add);
};
*/

class setting_cmd
{
public:
	setting_cmd() 
	{
		newlineChar_setting = ';';
		delimiterChar_setting = '=';
	}
	void loop()
	{
		String rx = Serial.readStringUntil(newlineChar_setting);
		if (rx != "")
		{
			Serial.println("receiver feom Serial " + rx);
			cmd_read_data(rx);
		}
	}
	void print()
	{
		Serial.println(F("Serial terminal usage:"));

		for (int i = 0; i < list_text_.getSize(); i++)
			Serial.println(list_command_[i] + "\t" + list_text_[i]);
		Serial.println("e\tend");
	}
	void add_command(String cmd, String text, int address)
	{
		list_command_.add(cmd);
		list_text_.add(text);
		list_address_.add(address);
	}
	void cmd_read_data(String cmd)
	{
		if (cmd == "e")
			ESP.restart();
		StringSplitter* Split = new StringSplitter(cmd, delimiterChar_setting, 2);
		int n = Split->getItemCount();
		if (n != 2)
			return;

		String cmd_ = Split->getItemAtIndex(0);
		String data_ = Split->getItemAtIndex(1);

		for (int i = 0; i < list_command_.getSize(); i++)
		{
			if (list_command_[i] == cmd_)
			{
				write_String_eeprom(list_address_[i], data_);
				Serial.println("save " + read_String_eeprom(list_address_[i]) + " in address " + String(list_address_[i]));
			}
		}
		print();
	}


private:
	char newlineChar_setting = '\n';
	char delimiterChar_setting = ' ';

	List<String> list_command_;
	List<String> list_text_;
	List<int> list_address_;

	void write_String_eeprom(int add, String data)
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
	String  read_String_eeprom(int add)
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
	void read_setting(String& MQTT_url_, int& MQTT_port_, String& MQTT_user_, String& MQTT_pass_, String& ESP_type_, String& ESP_SN_, String& DES_key_, String& WiFi_SSID_, String& WiFi_PASS_)
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

};

#endif

