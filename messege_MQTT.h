// messege_MQTT.h

#ifndef _messege_MQTT_h
#define _messege_MQTT_h

#include <EEPROM.h>
#include <PubSubClient.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Arduino.h>

class messege
{
public:
	messege() {}
	messege(String topic_ , String payload_)
	{
		topic = topic_;
		payload = payload_;
		//is_ok = true;
	}
	String topic;
	String payload;
	bool retained;
	//bool is_ok;
};


class MQTT
{

public:
	MQTT() {}
	void set_wifi(String WiFi_SSID, String WiFi_PASS);
	void set_server(String MQTT_url_, int MQTT_port_);

	void bigen(String MQTT_user_, String MQTT_pass_);
	void connect();
	void reconnect();
	void desconnect();
	bool is_connect();
	void set_topic(String topic_messege);
	void send_messege(messege mm);
	//messege receive_messege();
	void loop();
private:
	static void mqtt_callback(char* topic, byte* payload, unsigned int length);

	WiFiClient espClient;
	PubSubClient client = PubSubClient(espClient);
	String MQTT_user;
	String MQTT_pass;
	String MQTT_url;
	int MQTT_port;

	String WiFi_SSID;
	String WiFi_PASS;///////
};///////

#endif

