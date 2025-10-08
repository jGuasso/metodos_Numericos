#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAX_ITERACOES 1000000000

const double EPSILON = 0.00000001;

void trocaLinhas(double **l1,double **l2){
    double *temp = *l1;
    *l1 = *l2;
    *l2 = temp;
}

/*Critério da Diagonal Dominante*/
bool converge(double **m, int n){
    double S;
    for (int i = 0; i < n; i++)
    {
        S = 0;
        for (int j = 0; j < n; j++)
        {
            if (i!=j)
            {
                S += fabs(m[i][j]);
            }
        }

        if (fabs(m[i][i])<=S)
        {
            return false;
        }
        
    }
    return true;
}

void organiza_matriz(double **m, int n){
    int max, imax;
    for (int i = 0; i < n; i++)
    {
        max = fabs(m[i][i]);
        imax = i;
        for (int j = i+1; j < n; j++)
        {
            if (fabs(m[j][i])>max)
            {
                max = fabs(m[j][i]);
                imax = j;
            }
        }
        trocaLinhas(&m[i],&m[imax]);
    }
}

bool verifica_erro(double *x, double *x_ant, int n){
    double dividendo=0, divisor=0, k;
    for (int i = 0; i < n; i++)
    {
        k = x[i]-x_ant[i];
        dividendo+= k*k;
        divisor+=x[i]*x[i];
    }
    if (divisor == 0) return true;
    return (sqrt(dividendo)/sqrt(divisor)) < EPSILON;
}

void gauss_jacobi(double **m, int n, double *x){
    organiza_matriz(m,n);
    if (!converge(m,n))
    {
        printf("A Matriz nao converge!\n");
        exit(1);
    }
    
    int k = 1;
    double *x_ant = (double*) malloc(sizeof(double) * n) ;
    double S;
    while (k<MAX_ITERACOES)
    {
        memcpy(x_ant,x,n*sizeof(double));
        
        for (int i = 0; i < n; i++)
        {
            S = 0;
            for (int j = 0; j < n; j++)
            {
                if (j!=i)
                {
                    S+=m[i][j]*x_ant[j];
                }
            }
            x[i] = (m[i][n] - S)/m[i][i];
        }

        if (k%1000 == 0 && verifica_erro(x,x_ant,n))
        {
            free(x_ant);
            return;
        }

        k++;
    }
    
    free(x_ant);
}

int main(){
    int n;
    double **m, *x;
    printf("Digite o {n} da matriz n:n\n");
    scanf("%d",&n);
    m = (double**)malloc(sizeof(double*)*n);
    x = (double*)malloc(sizeof(double)*n);
    printf("para cada linha da matriz digite os valores e o respectivo resultado em b\n");
    for (int i = 0; i < n; i++)
    {
        m[i] = (double*) malloc(sizeof(double) * (n+1));
        for (int j = 0; j < n+1; j++)
        {
            scanf("%lf",&m[i][j]);
        }
    }
    printf("Digite os %d valores iniciais para os xi:\n",n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf",&x[i]);
    }

    gauss_jacobi(m,n,x);
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %lf\n",i+1,x[i]);
    }
}