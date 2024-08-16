
#include "WiFi_Manager.h"

WiFi_Manager::WiFi_Manager() : server(80){}
void WiFi_Manager::handleRoot()
{
	Serial.println("send HTML");
	server.send(200, "text/html", HTML);
	Serial.println("end HTML");
}
void WiFi_Manager::handlePost()
{
	is_connect = true;

	String ssid_received = server.arg("network");
	String password_received = server.arg("password");
	Serial.print("SSID ");
	Serial.println(ssid_received);
	Serial.print("PASS ");
	Serial.println(password_received);

	EEPROM.begin(512);
	WIFI_SSID_setting(ssid_received);
	WIFI_PASS_setting(password_received);

	ESP.restart();
}

void WiFi_Manager::begin(String ssid, String password)
{
	Serial.println("start");

	ssid_ = ssid.c_str();
	password_ = password.c_str();

	//the HTML of the web page
	server.on("/", std::bind(&WiFi_Manager::handleRoot, this));
	//handling receiving inputs from the web page
	server.on("/post", std::bind(&WiFi_Manager::handlePost, this));
	server.begin();
	WiFi.softAP(ssid, password); //begin WiFi access point

	Serial.println("end");
}
void WiFi_Manager::loop(void)
{
		server.handleClient(); //handle web servers' clients
}

void WiFi_Manager::WIFI_SSID_setting(String data)
{
	write_String_eeprom(400, data);
	Serial.print("EEPROM << WiFi_SSID = ");	
	data = read_String_eeprom(400);
	Serial.print(data);
	Serial.println();
}
void WiFi_Manager::WIFI_PASS_setting(String data)
{
	write_String_eeprom(450, data);
	Serial.print("EEPROM << WiFi_PASS = ");
	data = read_String_eeprom(450);
	Serial.print(data);
	Serial.println();
}
void WiFi_Manager::write_String_eeprom(int add, String data)
{
	int _size = data.length();
	int i;
	for (i = 0; i < _size; i++)
	{
		EEPROM.write(add + i, data[i]);
	}
	EEPROM.write(add + _size, '\0');   //Add termination null character for String Data
	EEPROM.commit();
}
String  WiFi_Manager::read_String_eeprom(int add)
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

String WiFi_Manager::get_WIFI_SSID_setting()
{
	return read_String_eeprom(400);
}
String WiFi_Manager::get_WIFI_PASS_setting()
{
	return read_String_eeprom(450);
}
