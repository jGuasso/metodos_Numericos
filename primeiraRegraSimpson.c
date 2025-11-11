#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x){
    return x*x*x;
}

double Integracao(double a, double b, double h){
    double x0=a, x1, x2, area=0;
    while (x0 < b)
    {
        x1= x0+h;
        x2= x1+h;
        area+= h*(func(x0)+4*func(x1)+func(x2))/3;
        x0=x2;
    }
    
    return area;
}

int main(){
    int n;
    double a, b;
    printf("Intervalo de integracao (a b):\n");
    scanf("%lf",&a);
    scanf("%lf",&b);
    printf("Numero de subintervalos (Deve ser um numero par)\n");
    scanf("%d",&n);
    if (n<=0)
    {
        printf("Erro, passo negativo ou igual a 0\n");
        return 1;
    }
    n = n%2==1?n+1:n;
    
    printf("%lf\n",Integracao(a,b,(b-a)/n));
}