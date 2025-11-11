#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x){
    return x*x*x;
}

double Integracao(double a, double b, double h){
    double x0=a, x1, area=0;
    while (x0 < b)
    {
        x1= x0+h<b ? x0+h : b;
        area+= (func(x0)+func(x1))*(x1-x0)/2;
        x0=x1;
    }
    
    return area;
}

int main(){
    double a, b;
    int n;
    printf("Intervalo de integracao (a b):\n");
    scanf("%lf",&a);
    scanf("%lf",&b);
    printf("Numero de subintervalos\n");
    scanf("%d",&n);
    if (n<=0)
    {
        printf("Erro, passo negativo ou igual a 0\n");
        return 1;
    }
    printf("%lf\n",Integracao(a,b,(b-a)/n));
}