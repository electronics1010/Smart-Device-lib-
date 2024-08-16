// 
// 
// 

#include "system_device.h"


#include "WiFi_Manager.h"

void SYSTEM_DEVICE::begin()
{
	pinMode(led, OUTPUT);
	digitalWrite(led, 0);

	delay(2000);
	Serial.setTimeout(1000);
	Serial.println();
	Serial.println("start");
	digitalWrite(led, 1);
	delay(2000);

	read_setting(MQTT_url, MQTT_port, MQTT_user, MQTT_pass, ESP_type, ESP_SN, DES_key, WiFi_SSID, WiFi_PASS);

	//cc = cipher_data(DES_key);

	digitalWrite(led, 0);
	MQTT_topic = ESP_type + "/" + ESP_SN + "";
	mqtt_.set_wifi(WiFi_SSID, WiFi_PASS);
	mqtt_.set_server(MQTT_url, MQTT_port);
	mqtt_.bigen(MQTT_user, MQTT_pass);
	mqtt_.connect();
	mqtt_.set_topic(MQTT_topic);

	mqtt_.loop();
	digitalWrite(led, 1);

}
void SYSTEM_DEVICE::loop()
{
	if (mqtt_.is_connect() == 0)
		mqtt_.reconnect();
	mqtt_.loop();

}
void SYSTEM_DEVICE::send_data(String topic, String message)
{
	topic =  MQTT_topic +  "/" + topic;
	//message = cc.encryption(message);
	mqtt_.send_messege(messege(topic, message));
}
void SYSTEM_DEVICE::send_data(messege message_)
{
	message_.topic =  MQTT_topic + "/" + message_.topic;

	//message_.payload = cc.encryption(message_.payload);
	mqtt_.send_messege(message_);
}
void SYSTEM_DEVICE::send_data(String String_message_)
{
	String	topic = MQTT_topic;
	messege mm = messege(topic, String_message_);
	//message = cc.encryption(message);
	mqtt_.send_messege(mm);

}
void SYSTEM_DEVICE::set_topic(String topic)
{
	mqtt_.set_topic(MQTT_topic + "/" + topic);
}
void SYSTEM_DEVICE::setting_WIFI()
{

	WiFi_Manager WM = WiFi_Manager();
	WM.begin("amm", "123456789");
	while (true)
		WM.loop();
}
void SYSTEM_DEVICE::setting_Serial()
{
	setting_cmd cmd = setting_cmd();

	digitalWrite(led, 0);

	cmd.add_command("1", "MQTT url", 50);
	cmd.add_command("2", "MQTT port", 100);
	cmd.add_command("3", "MQTT user", 150);
	cmd.add_command("4", "MQTT pass", 200);
	cmd.add_command("5", "ESP type", 250);
	cmd.add_command("6", "ESP SN", 300);
	cmd.add_command("7", "DES key", 350);
	cmd.add_command("8", "WiFi SSI ", 400);
	cmd.add_command("9", "WiFi PASS", 450);
	cmd.print();

	while (true)
	{
		cmd.loop();
	}
}


