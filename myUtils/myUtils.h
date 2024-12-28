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


boolean sommerZeit_EU(int year, byte month, byte day, byte hour, byte tzHours);

// Hilfsroutine weil Arduino kein Serial.printf hat
//  https://www.e-tinkers.com/2020/01/do-you-know-arduino-sprintf-and-floating-point/
//  https://en.cppreference.com/w/cpp/language/parameter_pack
//info: geht nur wenn im Headerfile. Prüfen warum nicht im cpp ????
template <typename... argsType>
void Serial_printf(const char* str, argsType... args) {
  int len = snprintf(NULL, 0, str, args...);
  if (len) {
    char buff[len + 1];
    snprintf(buff, len + 1, str, args...);
    Serial.print(buff);
  }
}

/*
char *str[] = {"this is test", "a", "b", "c", "d"};

    if (pos=in_array(str, 5, "c", strcmp) >=0 )
        printf("yes POS:%i\n",pos);
    else
        printf("no\n");
    }

*/

/* https://stackoverflow.com/questions/13814167/c-function-like-in-array-in-php
typedef int (*cmpfunc)(void *, void *);

int in_array(void *array[], int size, void *lookfor, cmpfunc cmp)
{
    int i;

    for (i = 0; i < size; i++)
        if (cmp(lookfor, array[i]) == 0)
            return i;
    return -1;
}
*/

#endif