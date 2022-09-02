#include <stdlib.h>
#include <stdio.h>
#include "controller.h"
void menu()
{
    int mode;
    printf("Escolha o modo para a temperatura de referencia (TR):\n");
    printf("[0] Potenciometro\n");
    printf("[1] Terminal\n");
    printf("Escolha o modo para a temperatura de referencia: ");
    scanf("%d", &mode);
    if (mode == 0)
    {
        set_mode(0);
    }
    else if (mode == 1)
    {
        float temp_ref;
        printf("Temperatura de referencia: ");
        scanf("%f", &temp_ref);
        set_pid_ref(temp_ref);
        set_mode(1);
    }
}
