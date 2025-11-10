#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ** interpolacao_definicao(int n, double* x_arr, double* y_arr){
    double** A = (double**) malloc(sizeof(double*)*n);
    for (int i = 0; i < n; i++)
    {
        A[i] = (double*) malloc(sizeof(double)*(n+1));
        double x_pow = 1;
        for (int j = 0; j < n; j++)
        {
            A[i][j]=x_pow;
            x_pow*=x_arr[i];
        }
        A[i][n]=y_arr[i];
    }
    return A;
}

void trocaLinhas(double **l1,double **l2){
    double *temp = *l1;
    *l1 = *l2;
    *l2 = temp;
}

double* escalonamento(double **m, int n){

    for (int i = 0; i < n; i++)
    {
        int j;

        for (j = i; j < n && m[j][i]==0; j++);
        if (j<n) trocaLinhas(&m[i],&m[j]);
        else continue;

        double a = m[i][i];
        for (j = i; j < n+1; j++)
        {
            m[i][j] /= a;
        }
        

        for ( j = 0; j < n; j++)
        {
            if (j==i)
                continue;
            
            double d = m[j][i]/m[i][i];
            for (int k = i; k < n+1; k++)
            {
                m[j][k] = m[j][k]- (d* m[i][k]);
            }
        }
    }
    double *x = (double*) malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++)
    {
        x[i] = m[i][n];
    }
    
    return x;
}

int main(){
    int n;
    printf("Numero de pontos: ");
    scanf("%d",&n);
    double* x_arr = (double*) malloc(sizeof(double)*n);
    double* y_arr = (double*) malloc(sizeof(double)*n); 

    for (int i = 0; i < n; i++)
    {
        printf("Ponto %d (x y): ",i+1);
        scanf("%lf",&x_arr[i]);
        scanf("%lf",&y_arr[i]);
    }
    
    double **A = interpolacao_definicao(n,x_arr,y_arr);

    double *a = escalonamento(A,n);
    for (int i = 0; i < n; i++)
    {
        printf("a%d=%lf\n",i,a[i]);
    }
    double x,r,xpow;
    while (1)
    {
        printf("Digite o valor de x:\n");
        scanf("%lf",&x);
        xpow=1;
        r=0;
        for (int i = 0; i < n; i++)
        {
            r+=a[i]*xpow;
            xpow*=x;
        }
        printf("%lf\n",r);
    }
    
}