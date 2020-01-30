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
	   #define DEBUG_PRINTF(...) DEBUG_ZIEL.printf( __VA_ARGS__ )
      #define DEBUG_INFO(x)     DEBUG_ZIEL <<"**** F:"<<__FUNCTION__ <<" L:"<< __LINE__ <<" # "<< x << endl   // Funtionsname, Zeilennummer und Parameter anzeigen
      #define DEBUG_VAR(x)      DEBUG_ZIEL << (#x) << " >" <<(x) << "<" << endl                               // Variablenname und Wert anzeigen
      #define DEBUG_SHOW(x)                   (#x) << " >" <<(x) << "<"                                       // Variablenname und Wert innerhalb anderen (Debug)-Prints anzuzeigen
   #else
      #define DEBUG(d)  {}
      #define DEBUG_PRINT(x)
      #define DEBUG_PRINTLN(x)
      #define DEBUG_PRINTF(x)
      #define DEBUG_INFO(x)
      #define DEBUG_VAR(x)
      #define DEBUG_SHOW(x)
   #endif

#endif