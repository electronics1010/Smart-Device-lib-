// 
// 
// 

#include "messege_MQTT.h"

void MQTT::set_wifi(String WiFi_SSID_, String WiFi_PASS_)
{
	WiFi_SSID = WiFi_SSID_;
	WiFi_PASS = WiFi_PASS_;
}
void MQTT::set_server(String MQTT_url_, int MQTT_port_)
{
	MQTT_url = MQTT_url_;
	MQTT_port = MQTT_port_;

	client.setServer(MQTT_url.c_str(), MQTT_port);
}
void MQTT::bigen(String MQTT_user_, String MQTT_pass_)
{
	MQTT_user = MQTT_user_;
	MQTT_pass = MQTT_pass_;

	client.setServer(MQTT_url.c_str(), MQTT_port);

	connect();
	client.setCallback(mqtt_callback);

}
void MQTT::connect()
{
	if (!espClient.connected())
	{
		Serial.print("Connecting to WiFi : ");
		Serial.print(WiFi_SSID);
		Serial.print(" ");
		Serial.print(WiFi_PASS);

		WiFi.begin(WiFi_SSID, WiFi_PASS, 6);

		while (WiFi.status() != WL_CONNECTED)
		{

			Serial.print(".");
			delay(1000);
		}

		Serial.println("Connected");
	}

	if (!client.connected())
	{
		String clientId = "device" + String(random(0xffff), HEX);
		Serial.print("Connecting to MQTT broker ");
		Serial.print(MQTT_url + ":");
		Serial.print(MQTT_port);
		while (!client.connect(clientId.c_str(), MQTT_user.c_str(), MQTT_pass.c_str()))
		{
			Serial.print(".");
			delay(1000);
		}
		Serial.println("Connected to MQTT broker");
	}

}
void MQTT::reconnect()
{

	if (!client.connected())
	{
		connect();
	}

}
void MQTT::desconnect()
{
	if (client.connected())
	{
		client.disconnect();
	}
}
bool MQTT::is_connect()
{
	return client.connected();
}
void MQTT::set_topic(String topic_messege)
{

	if (client.connected())
	{
		client.subscribe(topic_messege.c_str());

		Serial.print("subscribe ");
		Serial.println(topic_messege.c_str());

	}
}
void MQTT::send_messege(messege mm)
{
	String topic = mm.topic;
	String payload = mm.payload;
	//payload = DES_encryption(payload);
	//if (mm.is_ok)
	if (client.connected())
	{
		client.publish(topic.c_str(), payload.c_str());

		Serial.print("send ");
		Serial.print(topic);
		Serial.print("=");
		Serial.println(payload);
	}

}
/*
messege MQTT::receive_messege()
{
	return read_messege_eeprom();

}
*/
void MQTT::loop()
{
	client.loop();
}
