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
      #ifndef DEBUG__ZIEL
        #define DEBUG__ZIEL Serial   // Standardziel für Debugmeldungen
      #endif
      #ifndef DEBUG__
        #define DEBUG__(d) {d;}                       // ganzen Block nur bei DEBUG_EIN ausführen
      #endif
      #ifndef DEBUG__PRINT
        #define DEBUG__PRINT(x)    DEBUG__ZIEL.print(x)
      #endif
      #ifndef DEBUG__PRINTLN
        #define DEBUG__PRINTLN(x)  DEBUG__ZIEL.println(x)
      #endif
      #ifndef DEBUG__PRINTF
        #if defined(__AVR__)       // Arduino hat kein printf deshalb über snprintf mit Buffer
                                  // https://www.e-tinkers.com/2020/01/do-you-know-arduino-sprintf-and-floating-point/
          extern char myDebugBuffer[_MYDEBUGPRINTFBUFFER_SIZE];
          #define DEBUG_PRINTF(...) {  snprintf(myDebugBuffer,sizeof(myDebugBuffer),__VA_ARGS__); DEBUG_ZIEL.print(myDebugBuffer);}
        #else
          #define DEBUG__PRINTF(...) DEBUG__ZIEL.printf( __VA_ARGS__ )
        #endif
      #endif
      #ifndef DEBUG__INFO
        #define DEBUG__INFO(x)     DEBUG__ZIEL <<"**** F:"<<__FUNCTION__ <<" L:"<< __LINE__ <<" # "<< x << endl   // Funtionsname, Zeilennummer und Parameter anzeigen
      #endif
      #ifndef DEBUG__VAR
        #define DEBUG__VAR(x)      DEBUG__ZIEL << (#x) << " >" <<(x) << "<" << endl                               // Variablenname und Wert anzeigen
      #endif
      #ifndef DEBUG__SHOW
        #define DEBUG__SHOW(x)                   (#x) << " >" <<(x) << "<"                                       // Variablenname und Wert innerhalb anderen (Debug)-Prints anzuzeigen
      #endif
        #ifndef ESP32
          #define ARDUHAL_LOG_COLOR_E
          #define ARDUHAL_LOG_COLOR_W
          #define ARDUHAL_LOG_COLOR_I
          #define ARDUHAL_LOG_COLOR_D
          #define ARDUHAL_LOG_COLOR_V
          #define ARDUHAL_LOG_RESET_COLOR
          #define ARDUHAL_LOG_FORMAT(letter, format)  ARDUHAL_LOG_COLOR_ ## letter "[" #letter "][%s:%u] %s(): " format ARDUHAL_LOG_RESET_COLOR "\r\n", __FILE__, __LINE__, __FUNCTION__

      #endif
      #ifndef LOG__E
        #define LOG__E(format, ...)DEBUG_PRINTF(ARDUHAL_LOG_FORMAT(E, format), ##__VA_ARGS__)
      #endif
   #else  // Debug ist ausgeschaltet
      #define DEBUG__(d)  {}
      #define DEBUG__PRINT(x)
      #define DEBUG__PRINTLN(x)
      #define DEBUG__PRINTF(...)
      #define DEBUG__INFO(x)
      #define DEBUG__VAR(x)
      #define DEBUG__SHOW(x)
      #define LOG__E(format, ...)
   #endif

#endif