  #if defined(__AVR__)
      #define _MYDEBUGPRINTFBUFFER_SIZE  128
  #else
      #define _MYDEBUGPRINTFBUFFER_SIZE  1
  #endif

#pragma once
#ifndef myDEBUG_H
  #define myDEBUG_H

/*
*      Ausgabe von Debugmeldungen
*
*      Wenn Meldungen ausgegeben werden sollen, vor dem include-Befehl
*        #define DEBUG_EIN
*      schreiben
*
*     Standardmässig werden die Debugmeldungen auf "Serial" ausgegeben*
*     Durch setzen von DEBUG_ZIEL kann ein anderes Ziel angegeben werden  z.B. #define DEBUG_ZIEL Serial3
*
 */

   #ifdef DEBUG_EIN
      #include <Streaming.h>
      #ifndef DEBUG_ZIEL
         #define DEBUG_ZIEL Serial   // Standardziel für Debugmeldungen
      #endif

      #define DEBUG(d) {d;}                                                                                   // ganzen Block nur bei DEBUG_EIN ausführen
      #define DEBUG_PRINT(x)    DEBUG_ZIEL.print(x)
      #define DEBUG_PRINTLN(x)  DEBUG_ZIEL.println(x)
      #if defined(__AVR__)       // Arduino hat kein printf deshalb über snprintf mit Buffer
        extern char myDebugBuffer[_MYDEBUGPRINTFBUFFER_SIZE];
        #define DEBUG_PRINTF(...) {  snprintf(myDebugBuffer,sizeof(myDebugBuffer),__VA_ARGS__); DEBUG_ZIEL.print(myDebugBuffer);}
      #else
        #define DEBUG_PRINTF(...) DEBUG_ZIEL.printf( __VA_ARGS__ )
      #endif
      #define DEBUG_INFO(x)     DEBUG_ZIEL <<"**** F:"<<__FUNCTION__ <<" L:"<< __LINE__ <<" # "<< x << endl   // Funtionsname, Zeilennummer und Parameter anzeigen
      #define DEBUG_VAR(x)      DEBUG_ZIEL << (#x) << " >" <<(x) << "<" << endl                               // Variablenname und Wert anzeigen
      #define DEBUG_SHOW(x)                   (#x) << " >" <<(x) << "<"                                       // Variablenname und Wert innerhalb anderen (Debug)-Prints anzuzeigen
   #else
      #define DEBUG(d)  {}
      #define DEBUG_PRINT(x)
      #define DEBUG_PRINTLN(x)
      #define DEBUG_PRINTF(...)
      #define DEBUG_INFO(x)
      #define DEBUG_VAR(x)
      #define DEBUG_SHOW(x)
   #endif

#endif