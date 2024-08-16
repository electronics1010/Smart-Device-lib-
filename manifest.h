// manifest.h

#ifndef _MANIFEST_h
#define _MANIFEST_h

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <EEPROM.h>


class manifest
{
public:

	manifest(String server, String path)
	{
		path_ = path;
		server_ = server;
	}
	bool get_manifest()
	{

		while (!connect_WiFi());

		String json = get_data();
		Serial.println(F("json"));
		Serial.println(json);
		return json_deserialize(json);
	}
	
	void save_to_eeprom()
	{

		write_String_eeprom(50, get_mqtt_url());
		write_String_eeprom(100, String(get_mqtt_port()));
		write_String_eeprom(150, get_mqtt_user());
		write_String_eeprom(200, get_mqtt_pass());
	}
	
	String get_mqtt_url()
	{
		Serial.print("mqtt_url = "); Serial.println(mqtt_url);
		return mqtt_url; 
	}
	String get_mqtt_user() 
	{
		Serial.print("mqtt_user = "); Serial.println(mqtt_user);
		return mqtt_user; 
	}
	String get_mqtt_pass() 
	{
	 	Serial.print("mqtt_pass = "); Serial.println(mqtt_pass);
		return mqtt_pass; 
	}
	String get_SQL_url()
	{
		Serial.print("SQL_url = "); Serial.println(SQL_url);
		return SQL_url;
	}
	String get_SQL_user() 
	{
		Serial.print("SQL_user = "); Serial.println(SQL_user);
		return SQL_user; 
	}
	String get_SQL_pass()
	{
		Serial.print("SQL_pass = "); Serial.println(SQL_pass);
		return SQL_pass;
	}
	int get_mqtt_port()
	{
		Serial.print("mqtt_port = "); Serial.println(mqtt_port);
		return mqtt_port;
	}
	int get_SQL_port()
	{
		Serial.print("SQL_port = "); Serial.println(SQL_port);
		return SQL_port;
	}

private:
	String  path_, server_;
	String mqtt_url, mqtt_user, mqtt_pass, SQL_url, SQL_user, SQL_pass;
	int mqtt_port, SQL_port;
	String get_data()
	{
		String webpageContent = "";

		// استعدادًا للاتصال بالخادم
		WiFiClient client;

		if (client.connect(server_, 80)) 
		{
			Serial.print("get manifest from"); Serial.print(server_ + path_);

			// إرسال طلب GET لاسترداد المحتوى
			client.print("GET " + path_ + " HTTP/1.1\r\n");
			client.print("Host: " + String(server_) + "\r\n");
			client.print("Connection: close\r\n\r\n");

			// انتظر بعض الوقت للحصول على البيانات
			delay(1000);

			// قراءة وتخزين البيانات المتلقاة
			bool headerPassed = false;
			while (client.available()) {
				String line = client.readStringUntil('\r');
				if (!headerPassed && line == "\n") {
					headerPassed = true;
				}
				else if (headerPassed) {
					webpageContent += line;
				}
			}

			client.stop();
		}

		return webpageContent;

	}
	bool json_deserialize(String json)
	{
		StaticJsonDocument<300> doc;


		DeserializationError error = deserializeJson(doc, json);
		if (error)
		{
			Serial.print(F("Json failed: "));
			Serial.println(error.f_str());
			return false;
		}

		mqtt_url = doc["mqtt_url"].as<String>();
		mqtt_port = doc["mqtt_port"];
		mqtt_user = doc["mqtt_user"].as<String>();
		mqtt_pass = doc["mqtt_pass"].as<String>();
		SQL_url = doc["SQL_url"].as<String>();
		SQL_port = doc["SQL_port"];
		SQL_user = doc["SQL_user"].as<String>();
		SQL_pass = doc["SQL_pass"].as<String>();


		return true;

	}

	WiFiClient cmd;
	WiFiClient data;

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

	bool connect_WiFi()
	{

		String WiFi_SSID_ = read_String_eeprom(400);
		String WiFi_PASS_ = read_String_eeprom(450);


		Serial.print("Connecting to WiFi : ");
		Serial.print(WiFi_SSID_);
		Serial.print(" ");
		Serial.print(WiFi_PASS_);

		WiFi.begin(WiFi_SSID_, WiFi_PASS_, 6);

		while (WiFi.status() != WL_CONNECTED)
		{

			Serial.print(".");
			delay(1000);
		}

		Serial.println("Connected");
		if (WiFi.status() == WL_CONNECTED)
			return true;
		else
			return false;

	}

};


#endif

