#include <stdlib.h>
#include <stdio.h>

typedef struct _polinomio_lagrange
{
    double *x_arr;
    int n;
    double *coef;
}Polinomio_Lag;

Polinomio_Lag cria_polinomio(const int n,double *x_arr,double *y_arr){
    Polinomio_Lag P;
    P.x_arr = x_arr;
    P.n = n;
    P.coef = (double*) malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++)
    {
        P.coef[i]=y_arr[i];
        for (int j = 0; j < n; j++)
        {
            if (i!=j)
            {
                P.coef[i]/=(x_arr[i]-x_arr[j]);
            }
        }
    }
    return P;
}

double resulta_polinomio(const double x,const Polinomio_Lag P){
    double r = 0;
    for (int i = 0; i < P.n; i++)
    {
        double k=1;
        for (int j = 0; j < P.n; j++)
        {
            if (i!=j)
            {
                k*=(x-P.x_arr[j]);
            }
            
        }
        r+=P.coef[i]*k;
    }
    return r;
}

int main(){
    int n;
    printf("Numero de pontos: \n");
    scanf("%d",&n);
    double* x_arr = (double*) malloc(sizeof(double)*n);
    double* y_arr = (double*) malloc(sizeof(double)*n); 
    double x;
    for (int i = 0; i < n; i++)
    {
        printf("Ponto %d (x y): ",i+1);
        scanf("%lf",&x_arr[i]);
        scanf("%lf",&y_arr[i]);
    }
    Polinomio_Lag P = cria_polinomio(n,x_arr,y_arr);
    while (1)    
    {
        printf("Digite o valor de x:\n");
        scanf("%lf",&x);
        printf("P(%lf)=%lf\n",x,resulta_polinomio(x,P));
    }
    
}