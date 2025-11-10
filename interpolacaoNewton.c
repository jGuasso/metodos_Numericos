#include <stdio.h>
#include <stdlib.h>

double* coeficientes_newton(int n, double* x_arr, double* y_arr){
    double** tabela = (double**)malloc(sizeof(double*)*n);
    for (int i = 0; i < n; i++)
    {
        tabela[i] = (double*)malloc(sizeof(double)*(n-i));
        tabela[i][0]=y_arr[i];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n-i; j++)
        {
            tabela[j][i]=(tabela[j+1][i-1]-tabela[j][i-1])/(x_arr[j+i]-x_arr[j]);
        }
    }
    return tabela[0];
    
}

double interpolacao_newton(int n, double* x_arr, double* coef, double x){
    if (n<=0)return 0;
    double r = coef[0];
    double dif=1;
    for (int i = 0; i < n-1; i++)
    {
        dif=(x-x_arr[i])*dif;
        r+=dif*coef[i+1];
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
    double* coef = coeficientes_newton(n,x_arr,y_arr);
    while (1)
    {
        printf("Digite o valor de x:\n");
        scanf("%lf",&x);
        printf("P(%lf)=%lf\n",x,interpolacao_newton(n,x_arr,coef,x));
    }
    

}