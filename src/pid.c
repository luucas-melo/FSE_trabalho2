#include "pid.h"
#include <stdio.h>

double saida_medida, sinal_de_controle;
double referencia = 0.0;
double Kp = 0.0; // Ganho Proporcional
double Ki = 0.0; // Ganho Integral
double Kd = 0.0; // Ganho Derivativo
int T = 1.0;     // Período de Amostragem (ms)
unsigned long last_time;
double erro_total, erro_anterior = 0.0;
int sinal_de_controle_MAX = 100.0;
int sinal_de_controle_MIN = -100.0;

void pid_configura_constantes(double Kp_, double Ki_, double Kd_)
{
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;
}

void pid_atualiza_referencia(float referencia_)
{
    referencia = (double)referencia_;
}

double pid_controle(double saida_medida)
{

    double erro = referencia - saida_medida;

    // printf("Temp: \t Temp Ref: \t Erro \t Erro Total: \n");
    erro_total += erro; // Acumula o erro (Termo Integral)

    // printf("%.2f\t", saida_medida);
    // printf("%.2f\t", referencia);
    // printf("%.2f\t", erro);
    // printf("%.2f\t", erro_total);
    // printf("\n");

    if (erro_total >= sinal_de_controle_MAX)
    {
        erro_total = sinal_de_controle_MAX;
    }
    else if (erro_total <= sinal_de_controle_MIN)
    {
        erro_total = sinal_de_controle_MIN;
    }

    double delta_error = erro - erro_anterior; // Diferença entre os erros (Termo Derivativo)
    erro_anterior = erro;

    sinal_de_controle = Kp * erro + (Ki * T) * erro_total + (Kd / T) * delta_error; // PID calcula sinal de controle

    if (sinal_de_controle >= sinal_de_controle_MAX)
    {
        sinal_de_controle = sinal_de_controle_MAX;
    }
    else if (sinal_de_controle <= sinal_de_controle_MIN)
    {
        sinal_de_controle = sinal_de_controle_MIN;
    }

    return sinal_de_controle;
}