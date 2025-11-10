#include <stdlib.h>
#include <stdio.h>


double* cria_polinomio(const int n,const double *x_arr,const double *y_arr){
    double* coef = (double*) malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++)
    {
        coef[i]=y_arr[i];
        for (int j = 0; j < n; j++)
        {
            if (i!=j)
            {
                coef[i]/=(x_arr[i]-x_arr[j]);
            }
        }
    }
    return coef;
}

double resulta_polinomio(const double x,const double *coef,const double *x_arr,const int n){
    double r = 0;
    for (int i = 0; i < n; i++)
    {
        double k=1;
        for (int j = 0; j < n; j++)
        {
            if (i!=j)
            {
                k*=(x-x_arr[j]);
            }
            
        }
        r+=coef[i]*k;
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
    double* coef = cria_polinomio(n,x_arr,y_arr);
    while (1)    
    {
        printf("Digite o valor de x:\n");
        scanf("%lf",&x);
        printf("P(%lf)=%lf\n",x,resulta_polinomio(x,coef,x_arr,n));
    }
    
}