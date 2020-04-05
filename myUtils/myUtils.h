#pragma once
#ifndef myUTILS_H_
  #define myUTILS_H_

#include <Arduino.h>


String split(String s, char separator, int index);

void removeMultiBlanks(char* str);         // Mehrfache Leerzeichen entfernen

void removeChar(char* str, char ch=' ');   // alle Zeichen ch entfernen
inline void removeSpace(char* str) { removeChar(str, ' '); }        // alle Leerzeichen entfernen

char* removeChar(char* str_in, char* str_out, char ch=' ');    // alle Zeichen ch entfernen
inline char* removeSpace(char* str_in, char* str_out) { return removeChar(str_in, str_out, ' '); }        // alle Leerzeichen entfernen


char *XremoveSpaces(char *str);

char* LTrim(char* szX);

char* RTrim(char* szX);

char* Trim(char* szX);

void trim(char** arg, char c=' ');


// converts character array
// to string and returns it
String convertToString(char* a, int size, bool add0 = false);

//https://circuits4you.com/2019/03/21/esp8266-url-encode-decode-example/
unsigned char h2int(char c);
String urldecode(String str);

String urlencode(String str);
#endif