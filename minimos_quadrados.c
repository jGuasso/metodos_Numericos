#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int main(){
    int n, m;
    printf("Digite o grau do polinomio: ");
    scanf("%d", &m);
    printf("Digite o numero de pontos: ");
    scanf("%d", &n);

    double **A = (double **)malloc((m + 1) * sizeof(double *));
    for(int i = 0; i <= m; i++){
        A[i] = (double *)malloc((m + 2) * sizeof(double));
    }

    for(int i = 0; i < n; i++){
        double x, y;
        printf("Digite o ponto %d (x y): ", i + 1);
        scanf("%lf %lf", &x, &y);

        for(int j = 0; j <= 2*m; j++){
            double x_pow = pow(x, j);
            if(j < m + 1){
                A[j][m + 1] += y * x_pow;
            }
            for(int k = j<m?0:j-m; k <= m; k++){
                if(j-k<0){
                    break;
                }
                if(j - k <= m){
                    A[k][j-k] += x_pow;
                }
            }

        }
        
    }

    escalonamento(A, m + 1);
    double* coeficientes = substituicao(A, m + 1);
    printf("Coeficientes do polinomio ajustado:\n");
    for(int i = 0; i <= m; i++){
        printf("a[%d] = %.6lf\n", i, coeficientes[i]);
    }

}