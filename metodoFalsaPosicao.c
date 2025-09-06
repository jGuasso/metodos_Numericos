#include <math.h>
#include <stdbool.h>
#include <stdio.h>

double metodo_falsa_posicao(double (*funcao)(double), double a, double b, double epsilon){
    double fa = funcao(a), fb = funcao(b), x, fx;

    while (fabs(a-b)>epsilon)
    {
        x = (a*fb - b*fa)/(fb-fa);
        fx = funcao(x);
        if (fabs(fx) < epsilon)
            return x;
        if (fa*fx < 0)
        {
            b = x;
            fb = fx;
        }else
        {
            a = x;
            fa = fx;
        }
    }
    return (a*fb - b*fa)/(fb-fa);
    
}

bool bolzano(double (*funcao)(double),double a, double b){
    return funcao(a) * funcao(b) < 0;
}

double fx(double x){
    return (8*log2(x)) - x;
}


int main(){
    double a, b, episolon,resultado;

    printf("a, b, episolon:\n");
    scanf("%lf, %lf, %lf",&a, &b, &episolon);
    if (!bolzano(fx,a,b))
    {
        printf("\nIntervalo Invalido!\n");
    }
    resultado = metodo_falsa_posicao(fx,a,b,episolon);
    printf("\n%lf\n",resultado);
}