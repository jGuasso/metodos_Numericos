#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double newton_raphson(double(*funcao)(double),double(*derivada)(double),double x,double epsilon){
    while (fabs(funcao(x))>epsilon)
    {
        if (fabs(derivada(x))<0.000001)
        {
            printf("ERRO: f'(%lf) = 0",x);
            exit(1);
        }
        
        x = x - funcao(x)/derivada(x);
    }
    return x;
}

double fx(double x){
    return x*x - 2;
}

double dx(double x){
    return 2*x;
}

int main(){
    double a,episolon,resultado;
    printf("a episolon:\n");
    scanf("%lf %lf",&a, &episolon);
    resultado = newton_raphson(fx,dx,a,episolon);
    printf("\n%lf\n",resultado);
}