// 
// 
// 

#include "Splitte_String.h"


void Splitter_String::Splitter_data(const String& inputString, char delimiter, String* outputArray)
{
	int arraySize = Splitter_item(inputString, delimiter);
	int stringLength = inputString.length();
	int arrayIndex = 0;
	int startIndex = 0;

	for (int i = 0; i < stringLength; i++) {
		if (inputString.charAt(i) == delimiter || i == stringLength - 1) {
			int substringLength = i - startIndex + 1;

			if (i == stringLength - 1 && inputString.charAt(i) != delimiter) {
				substringLength++;
			}

			if (arrayIndex < arraySize) {
				outputArray[arrayIndex] = inputString.substring(startIndex, startIndex + substringLength - 1);
				arrayIndex++;
			}

			startIndex = i + 1;
		}
	}
}
int Splitter_String::Splitter_item(String text, char delimiter)
{
	int n = 1;
	for (int i = 0; i < text.length(); i++)
		if (text[i] == delimiter)
			n++;
	return n;
}

