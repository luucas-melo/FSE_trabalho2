#include "i2c_lcd.h"
void display_message(const char *s)
{
    ClrLcd();
    typeln(s);
}

void display_air_fryer_info(float tr, float ti, int timer)
{
    ClrLcd();
    lcdLoc(LINE1);
    typeln("TI:");
    typeFloat(ti);
    typeln(" TR:");
    typeFloat(tr);

    lcdLoc(LINE2);
    typeln("TEMPO:");
    typeInt(timer);
    typeln("s");
}