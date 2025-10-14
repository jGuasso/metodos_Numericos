#include <stdio.h>
#include <math.h>

double metodo_das_secantes(double(*funcao)(double),double x1, double x2, double epsilon){
    double x0;

    while (fabs(funcao(x2))>epsilon)
    {
        x0 = x1;
        x1 = x2;
        x2 = x1 - (funcao(x1)*(x1-x0))/(funcao(x1)-funcao(x0));
    }
    return x2;    
}

double fx(double x){
    return 8*log2(x) - x;
}

int main(){
    double a,b,episolon,resultado;
    printf("a b episolon:\n");
    scanf("%lf %lf %lf",&a, &b, &episolon);
    resultado = metodo_das_secantes(fx,a,b,episolon);
    printf("\n%lf\n",resultado);
}