#ifndef pagine_h
#define pagine_h

#include "main.h"

/*	jquery.min.js version 3.2.1 - Contribution from https://esp32.com/viewtopic.php?t=11744

    size of original js file:  85 KB
    size in this source file: 148 KB
    size on ESP:               30 KB

 */
#define jquery_min_js_v3_2_1_gz_len 30178

extern PROGMEM const char jquery_min_js_v3_2_1_gz[];

extern WebServer webServer;
extern WiFiClient wifiClient;

void initIOT(void);

#endif // #ifndef pagine_h
