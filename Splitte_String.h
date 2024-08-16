// Splitte_String.h

#ifndef _Splitte_String_h
#define _Splitte_String_h
#include <Arduino.h>


class Splitter_String
{
public:
	Splitter_String() {}
	void Splitter_data(const String& inputString, char delimiter, String* outputArray);
	int Splitter_item(String text, char delimiter);
};

#endif

