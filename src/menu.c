#include <stdlib.h>
#include <stdio.h>
#include "controller.h"
#include "timer.h"
void menu()
{
    int mode = 0;
    printf("Escolha o modo da temperatura de referencia (TR):\n");
    printf("[0] Potenciometro\n");
    printf("[1] Terminal\n");
    scanf("%d", &mode);
    if (mode == 0)
    {
        set_mode(0);
    }
    else if (mode == 1)
    {
        float temp_ref;
        int time;
        printf("Temperatura de referencia: ");
        scanf("%f", &temp_ref);
        set_pid_ref(temp_ref);

        printf("Tempo: ");
        scanf("%d", &time);
        set_time(time);
        set_mode(1);
    }
}
