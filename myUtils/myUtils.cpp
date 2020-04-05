
#include <myUtils.h>

String split(String s, char separator, int index) {  // https://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string
  int separatorCnt = 0;                              // was für Stringarray https://stackoverflow.com/questions/9072320/split-string-into-string-array
  int rFromIndex   = 0;                              //  http://www.c-howto.de/tutorial/strings-zeichenketten/string-funktionen/string-zerteilen/
  int rToIndex     = -1;                             // http://ediy.com.my/tutorials/item/142-split-comma-or-any-other-character-delimited-string-into-an-array
  while (index >= separatorCnt) {
    rFromIndex = rToIndex + 1;
    rToIndex   = s.indexOf(separator, rFromIndex);
    if (index == separatorCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";  // nicht gefunden
      return s.substring(rFromIndex, rToIndex);        // gefunden
    } else
      separatorCnt++;
  }
  return "";  // nicht gefunden
}


// Mehrfache Leerzeichen entfernen
void removeMultiBlanks(char* str) {
  int i = 0, j = 0;
  while (str[i])  // bis zum Stringende =  \0  --> false
  {
    while (str[i] == ' ' && str[i + 1] == ' ') i++;  // mehrfache Leerzeichen überspringen (entfernen)
    str[j++] = str[i++];
  }
  str[j] = '\0';
}


// alle Zeichen  ch entfernen
void removeChar(char* str, char ch) {
  int i = 0, j = 0;
  while (str[i])  // bis zum Stringende =  \0  --> false
  {
    while (str[i] == ch) i++;  // Zeichen überspringen (entfernen)
    str[j++] = str[i++];
  }
  str[j] = '\0';
}
//inline void removeSpace(char* str) { removeChar(str, ' '); }    // im .h


// alle Leerzeichen entfernen
// char x[20];
// char *y;
// y = removeSpaces(test,x);
char* removeChar(char* str_in, char* str_out, char ch) {
  int i = 0, j = 0;
  while (str_in[i]) {
    if (str_in[i] != ' ') str_out[j++] = str_in[i];
    i++;
  }
  str_out[j] = '\0';
  return str_out;
}
//inline char* removeSpace(char* str_in, char* str_out) { return removeChar(str_in, str_out, ' '); }  // im .h


// alle Leerzeichen entfernen
void XremoveSpace(char* str) {
  char* str2 = str;
  do {
    if (*str2 != ' ') *str++ = *str2;
  } while (*str2++);
  *str = '\0';
}



// char x[20];
// char *y = x;
// y = removeSpaces(test);
char* XremoveSpaces(char* str) {
  int i = 0, j = 0;
  while (str[i]) {
    if (str[i] != ' ') str[j++] = str[i];
    i++;
  }
  str[j] = '\0';
  return str;
}

void ltrim(char* str) {
  if (' ' == str[0])
    while (' ' == (++str)[0])
      ;
}

char* LTrim(char* szX) {
  if (' ' == szX[0])
    while (' ' == (++szX)[0])
      ;
  return szX;
}

char* RTrim(char* szX) {
  int i = strlen(szX);
  while (' ' == szX[--i]) szX[i] = 0;
  return szX;
}

char* Trim(char* szX) {
  szX = LTrim(szX);
  szX = RTrim(szX);
  return szX;
}

void trim(char** arg, char c) {
  char* p = *arg;  // preserve the original string
  while (*p++)
    ;
  p--;
  while (c == *--p) *p = 0;  // deleting trailing spaces
  while (c == *(*arg)++)
    ;
  (*arg)--;  // ignoring leading spaces
}

// converts character array
// to string and returns it
String convertToString(char* a, int size, bool add0) {
  int i;
  String s = "";
  for (i = 0; i < size; i++) {
    s = s + a[i];
  }
  if (add0) s = s + "\0";
  return s;
}

// https://circuits4you.com/2019/03/21/esp8266-url-encode-decode-example/
unsigned char h2int(char c) {
  if (c >= '0' && c <= '9') {
    return ((unsigned char)c - '0');
  }
  if (c >= 'a' && c <= 'f') {
    return ((unsigned char)c - 'a' + 10);
  }
  if (c >= 'A' && c <= 'F') {
    return ((unsigned char)c - 'A' + 10);
  }
  return (0);
}
String urldecode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (size_t i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == '+') {
      encodedString += ' ';
    } else if (c == '%') {
      i++;
      code0 = str.charAt(i);
      i++;
      code1 = str.charAt(i);
      c     = (h2int(code0) << 4) | h2int(code1);
      encodedString += c;
    } else {
      encodedString += c;
    }

    // yield();
  }

  return encodedString;
}

String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;

  for (size_t i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c     = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      // encodedString+='\0';
    }
    // yield();
  }
  return encodedString;
}