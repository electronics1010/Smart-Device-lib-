
#ifndef _WIFI_MANAGER_h
#define _WIFI_MANAGER_h

#ifdef ESP32
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#else
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#endif
#include <EEPROM.h>


class WiFi_Manager
{
public:
	WiFi_Manager();
	void begin(String ssid, String password);
	void loop();

	String get_WIFI_SSID_setting();
	String get_WIFI_PASS_setting();

private:
	const char* ssid_ = "your_SSID";
	const char* password_ = "your_PASSWORD";
	void handleRoot();
	void handlePost();
	static void WIFI_SSID_setting(String data);
	static void WIFI_PASS_setting(String data);
	static void write_String_eeprom(int add, String data);
	static String  read_String_eeprom(int add);

	String* WIFI_netwonk;
	String HTML = "<!DOCTYPE html><html><head> <title>WiFi Settings</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <style> body { font-family: Arial, sans-serif; margin: 0; padding: 0; background-color: #f0f0f0; } .container { max-width: 600px; margin: 0 auto; padding: 20px; } select, input[type=password] { width: 100%; padding: 12px 20px; margin: 8px 0; display: inline-block; border: 1px solid #ccc; box-sizing: border-box; } button { background-color: #4CAF50; color: white; padding: 14px 20px; margin: 8px 0; border: none; cursor: pointer; width: 100%; } button:hover { opacity: 0.8; } </style> </head> <body> <form action=\\\"post\" method=\"POST\"> <div class=\"container\"> <label for=\"network\"><b>Network Name</b></label> <input type=\"text\" id=\"network\" name=\"network\" required> <option value=\"\">Select Network</option></select> <label for=\"psw\"><b>Password</b></label> <input type=\"password\" id=\"psw\" placeholder=\"Enter Password\" name=\"psw\" required> <input type=\"checkbox\" onclick=\"myFunction()\">Show Password <button type=\"button\" onclick=\"submitFunction()\">Save</button> </div> </form> <script> function myFunction() { var x = document.getElementById(\"psw\"); if (x.type === \"password\") { x.type = \"text\"; } else { x.type = \"password\"; } } function submitFunction() { var x = document.getElementById(\"network\").value; var y = document.getElementById(\"psw\").value; window.location.href = \"post?network=\" + x + \"&password=\" + y; }</script></body></html>";

	bool is_connect = false;
#ifdef ESP32
	WiFiServer server;
#else	
	ESP8266WebServer server;

#endif


};

#endif
