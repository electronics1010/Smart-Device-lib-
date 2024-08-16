

#include "Cipher.h"
#include <WString.h>
//#include <Splitte_String>

String cipher_data::Cipher(byte data[], int length)
{

	String d = "";
	for (byte i = 0; i < length; i++)
	{
		byte dk = data[i];
		byte kk = key[i % key.length()];
		char ck = dk ^ kk;
		d = d + (String)ck;
	}
	return d;
}
String cipher_data::encryption(String data)// تشفير
{
	int length = data.length();

	byte data_byte[length];
	for (int i = 0; i < length; i++)
		data_byte[i] = (byte)data[i];

	String encryption_byte = Cipher(data_byte, length);

	String ss = String((byte)encryption_byte[0]);
	for (int i = 1; i < length; i++)
		ss = ss + "," + String((byte)encryption_byte[i]);

	return ss;
}
String cipher_data::decryption(String data)// فك تشفير
{
	Splitter_String Split = Splitter_String();

	const int itemCount = Split.Splitter_item(data,',');
	String ss_[itemCount];
	Split.Splitter_data(data, ',', ss_);

	byte dd[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		String s = ss_[i];
		char c = s.toInt();
		dd[i] = c;
	}

	String ss = Cipher(dd, itemCount);

	return ss;
}
