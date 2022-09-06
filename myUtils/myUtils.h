#pragma once
#ifndef myUTILS_H_
  #define myUTILS_H_

#include <Arduino.h>

// https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func
#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))


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

//int strpos(const char *haystack, const char *needle);
int strpos(const char *haystack, const char *needle, int offset);
#endif