#pragma once
#ifndef myDEBUG_H
  #define myDEBUG_H

/*
*      Ausgabe von Debugmeldungen
*
*      Wenn Meldungen ausgegeben werden sollen, vor dem include-Befehl
*        #define DEBUG_EIN
*      schreiben
 */

   #ifdef DEBUG_EIN
      #include <Streaming.h>
      extern char myDebugBuffer[255];
      /*
      void DEBUG_SERIAL(char *format, ...)    //https://www.utopiamechanicus.com/article/sprintf-arduino/
      {
         va_list args;
         va_start (args,format);
         vsnprintf(myDebugBuffer,sizeof(myDebugBuffer),format,args);
         va_end (args);
         myDebugBuffer[sizeof(myDebugBuffer)/sizeof(myDebugBuffer[0])-1]='\0';
         Serial.print(myDebugBuffer);
      }
     */
         //https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
         //http://www.cplusplus.com/reference/cstdio/printf/
         //https://docs.microsoft.com/de-de/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=vs-2019
      #define DEBUG_SERIAL(...) {  snprintf(myDebugBuffer,sizeof(myDebugBuffer),__VA_ARGS__); Serial.print(myDebugBuffer);}
      //#define DEBUG_SERIAL2(fmt, ...) {  snprintf(myDebugBuffer,255,fmt, ##__VA_ARGS__); Serial.print(myDebugBuffer);}

      #define DEBUG(d) {d;}
      #define DEBUG_PRINT(x)  Serial.print(x)
      #define DEBUG_PRINTLN(x) Serial.println(x)
      #define DEBUG_INFO(x)  {Serial <<"**** F:"<<__FUNCTION__ <<" L:"<< __LINE__ <<" # "<< x << endl;}    // Funtionsname, Zeilennummer und Parameter anzeigen
      #define DEBUG_VAR(X) Serial << (#X) << "=" << ">" <<(X) << "<" << endl;                                           // Variablenname und Wert anzeigen
   #else
      #define DEBUG_SERIAL(...) {}
      #define DEBUG(d)  {}
      #define DEBUG_PRINT(x)
      #define DEBUG_PRINTLN(x)
      #define DEBUG_INFO(x)
      #define DEBUG_VAR(X)
   #endif

#endif