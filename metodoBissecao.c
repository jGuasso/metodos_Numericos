#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool bolzano(double (*funcao)(double),double a, double b){
    return funcao(a) * funcao(b) < 0;
}

double ponto_medio(double a, double b){
    return (a+b)/2;
}

double metodo_bissecao(double (*funcao)(double),double a, double b, double episolon){
    double pm,fpm,fa;
    fa=funcao(a);
    do
    {
        pm = ponto_medio(a,b);
        fpm = funcao(pm);
        if (fabs(fpm)<episolon)
            return pm;
        if (fa*fpm < 0){
            b = pm;
        }else
        {
            fa = fpm;
            a = pm;
        }
    }while (fabs(a-b)>episolon);
    
    return ponto_medio(a,b);
}

double fx(double x){
    return cos(x) - x;
}

int main(){
    double a, b, episolon,resultado;

    printf("a b episolon:\n");
    scanf("%lf %lf %lf",&a, &b, &episolon);
    if (!bolzano(fx,a,b))
    {
        printf("\nIntervalo Invalido!\n");
        return 1;
    }
    resultado = metodo_bissecao(fx,a,b,episolon);
    printf("\n%lf\n",resultado);
}