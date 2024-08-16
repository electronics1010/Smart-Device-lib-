// Cipher.h

#ifndef _Cipher_h
#define _Cipher_h

#include <WString.h>
#include <Splitte_String.h>

class cipher_data
{
public:
	cipher_data(String key_) 
	{
		key = key_;
	}
	String Cipher(byte data[], int length);
	String encryption(String data);
	String decryption(String data);
private:
	String key;

};

#endif

