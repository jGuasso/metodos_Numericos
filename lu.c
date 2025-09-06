#include <stdio.h>
#include <stdlib.h>

void trocaLinhas(double **l1,double **l2){
    double *temp = *l1;
    *l1 = *l2;
    *l2 = temp;
}

void printMatriz(double** m,int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2lf ",m[i][j]);
        }
        printf("\n");
    }   
}

void escalonamentoLU(double **LU, double** P, int n){

    for (int i = 0; i < n-1; i++)
    {
        int j;

        for (j = i; j < n && LU[j][i]==0; j++);
        if (j<n){
            trocaLinhas(&LU[i],&LU[j]);
            trocaLinhas(&P[i],&P[j]);
        }
        else continue;

        for ( j = i+1; j < n; j++)
        {
            double x = LU[j][i]/LU[i][i];
            for (int k = i; k < n; k++)
            {
                LU[j][k] = LU[j][k]- (x* LU[i][k]);
            }
            LU[j][i]=x;
        }
    }
}


double* substituicao(double** LU, double** P, double* b, int n){
    double *bl = (double*)malloc(sizeof(double)*n); 
    double *y = (double*)malloc(sizeof(double)*n);
    double *x = (double*)malloc(sizeof(double)*n);
    double aux;

    for (int i = 0; i < n; i++)
    {
        bl[i]=0;
        for (int j = 0; j < n; j++)
        {
            bl[i] += P[i][j]*b[j];
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        y[i] = bl[i];
        for (int j = 0; j < i; j++)
        {
            y[i] -= LU[i][j] * y[j];
        }
    }
    
    for (int i = n-1; i >= 0; i--)
    {
        aux = y[i];
        for (int j = i+1; j < n; j++)
        {
            aux-= LU[i][j]*x[j];
        }
        x[i] = aux/LU[i][i];
    }
    free(bl);
    free(y);
    return x;
}

int main(){
    double **A,**LU, **P;
    int n;
    printf("Digite o {n} da matriz n:n\n");
    scanf("%d",&n);
    A = (double **) malloc(sizeof(double*)*n);
    LU = (double **) malloc(sizeof(double*)*n);
    P = (double **) malloc(sizeof(double*)*n);
    printf("Digite os valores da matriz\n");
    for (int i = 0; i < n; i++)
    {
        A[i] = (double*)malloc(sizeof(double)*n);
        LU[i] = (double*)malloc(sizeof(double)*n);
        P[i] = (double*)malloc(sizeof(double)*n);
        for (int j = 0; j < n; j++)
        {
            if (j==i)
                P[i][j] = 1;
            else
                P[i][j] = 0;
            
            scanf("%lf",&A[i][j]);
            LU[i][j] = A[i][j];
        }
    }
    escalonamentoLU(LU,P,n);

    printf("\n Matriz LU:\n");
    printMatriz(LU,n);

    printf("\n Matriz P:\n");
    printMatriz(P,n);
    printf("\n");

    double *b = (double*)malloc(sizeof(double)*n);
    double *x = (double*)malloc(sizeof(double)*n);
    while (1)
    {
        printf("digite o vetor de %d elementos a ser utilizado\n",n);
        for (int i = 0; i < n; i++)
        {
            scanf("%lf",&b[i]);
        }
        x = substituicao(LU,P,b,n);
        for (int i = 0; i < n; i++)
        {
            printf("x%d = %lf\n",i+1,x[i]);
        }
        
    }
    
}