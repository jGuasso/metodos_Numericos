#include <stdio.h>
#include <stdlib.h>

void trocaLinhas(double **l1,double **l2){
    double *temp = *l1;
    *l1 = *l2;
    *l2 = temp;
}

void escalonamento(double **m, int n){

    for (int i = 0; i < n-1; i++)
    {
        int j;

        for (j = i; j < n && m[j][i]==0; j++);
        if (j<n) trocaLinhas(&m[i],&m[j]);
        else continue;

        for ( j = i+1; j < n; j++)
        {
            double x = m[j][i]/m[i][i];
            for (int k = i; k < n+1; k++)
            {
                m[j][k] = m[j][k]- (x* m[i][k]);
            }
        }
    }
    
}

double* substituicao(double **m, int n){
    double* x = (double*)malloc(sizeof(double)*n);
    double aux;
    for (int i = n-1; i >= 0; i--)
    {
        aux = m[i][n];
        for (int j = i+1; j < n; j++)
        {
            aux-= m[i][j]*x[j];
        }
        x[i] = aux/m[i][i];
    }
    return x;
}

void printMatriz(double** m,int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n+1; j++)
        {
            printf("%.2lf ",m[i][j]);
        }
        printf("\n");
    }   
}

int main(){
    int n;
    double **m, *x;
    printf("Digite o {n} da matriz n:n\n");
    scanf("%d",&n);
    m = (double**)malloc(sizeof(double*)*n);
    printf("para cada linha da matriz digite os valores e o respectivo resultado em b\n");
    for (int i = 0; i < n; i++)
    {
        m[i] = (double*) malloc(sizeof(double) * (n+1));
        for (int j = 0; j < n+1; j++)
        {
            scanf("%lf",&m[i][j]);
        }
    }
    escalonamento(m,n);
    printMatriz(m,n);
    x =substituicao(m,n);
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %lf\n",i+1,x[i]);
    }
}