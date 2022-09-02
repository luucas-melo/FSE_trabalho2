#include <i2c_lcd.h>
void display_message(const char *s)
{
    ClrLcd();
    typeln(s);
}

void display_air_fryer_info(float tr, float ti, int timer)
{
    ClrLcd();
    lcdLoc(LINE1);
    typeln(" TR:");
    typeFloat(tr);

    lcdLoc(LINE2);
    typeln("TI:");
    typeFloat(ti);

    typeln(" TIMER:");
    typeInt(timer);
}