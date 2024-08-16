// system_device.h

#ifndef _SYSTEM_DEVICE_h
#define _SYSTEM_DEVICE_h

#include "system_device.h"
#include "serial_setting.h"
#include "messege_MQTT.h"
#include "serial_setting.h"
#include "WiFi_Manager.h"
#include "manifest.h"
//#include "Cipher.h"
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Arduino.h>	

class SYSTEM_DEVICE
{
public:
	SYSTEM_DEVICE() {}

	String get_main_topic()
	{
		return MQTT_topic;
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
	bool setting_manifest()
	{
		manifest mf = manifest("internet-of-device.wuaze.com", "/manifest.json?i=2");
		if (mf.get_manifest())
		{
			mf.save_to_eeprom();
			return true;	
			Serial.print("geted manifest");
			
		}
		Serial.print("not geted manifest");

		return false;
	}


	void begin();
	void loop();
	void setting_WIFI();
	void send_data(String topic, String message);
	void send_data(messege message_);
	void send_data(String String_message_);
	void set_topic(String topic);
	void setting_Serial();

	int led = -1;
private:

	String MQTT_url = "95.212.13.205";
	int    MQTT_port = 1883;
	String MQTT_user = "amm";
	String MQTT_pass = "123";
	String ESP_type = "ammar";
	String ESP_SN = "almadi";
	String DES_key = "ammar almadi";
	String WiFi_SSID = "Wokwi-GUEST";
	String WiFi_PASS = "";

	String MQTT_topic;
	MQTT mqtt_ = MQTT();

	setting_cmd ss = setting_cmd();

	String read_String_eeprom(int add)
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
};



#endif

