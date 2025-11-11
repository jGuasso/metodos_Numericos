#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

__declspec(dllexport) double f1(double x) {
    return (x*x)-2;
}

__declspec(dllexport) double d1(double x){
    return 2*x;
}


/*
* Método da Bisseção
*/

__declspec(dllexport) bool bolzano(double (*funcao)(double),double a, double b){
    return funcao(a) * funcao(b) < 0;
}

__declspec(dllexport) double ponto_medio(double a, double b){
    return (a+b)/2;
}

__declspec(dllexport) double metodo_bissecao(double (*funcao)(double),double a, double b, double epsilon){
    double pm,fpm,fa;
    fa=funcao(a);
    while (fabs(a-b)>epsilon)
    {
        pm = ponto_medio(a,b);
        fpm = funcao(pm);
        if (fabs(fpm)<epsilon)
            return pm;
        if (fa*fpm < 0){
            b = pm;
        }else
        {
            fa = fpm;
            a = pm;
        }
    }
    return ponto_medio(a,b);
}

/*
* Método da Falsa Posição
*/

__declspec(dllexport) double metodo_falsa_posicao(double (*funcao)(double), double a, double b, double epsilon){
    double fa = funcao(a), fb = funcao(b), x, fx;

    while (fabs(a-b)>epsilon)
    {
        x = (a*fb - b*fa)/(fb-fa);
        fx = funcao(x);
        if (fabs(fx) < epsilon)
            return x;
        if (fa*fx < 0)
        {
            b = x;
            fb = fx;
        }else
        {
            a = x;
            fa = fx;
        }
    }
    return (a*fb - b*fa)/(fb-fa);
    

}

/*
* newton_raphson
*/

__declspec(dllexport) double newton_raphson(double(*funcao)(double),double(*derivada)(double),double x,double epsilon){
    while (fabs(funcao(x))>epsilon)
    {
        x = x - funcao(x)/derivada(x);
    }
    return x;
}

/*
* Método das secantes
*/

/*
* Mínimos Quadrados
*/

__declspec(dllexport) double metodo_das_secantes(double(*funcao)(double),double x1, double x2, double epsilon){
    double x0;

    while (fabs(funcao(x2))>epsilon)
    {
        x0 = x1;
        x1 = x2;
        x2 = x1 - (funcao(x1)*(x1-x0))/(funcao(x1)-funcao(x0));
    }
    return x2;    
}


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

__declspec(dllexport) double* minimos_quadrados(int m, int n, double x[], double y[]){
    double **A = (double **)malloc((m + 1) * sizeof(double *));
    for(int i = 0; i <= m; i++){
        A[i] = (double *)malloc((m + 2) * sizeof(double));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= 2*m; j++){
            double x_pow = pow(x[i], j);
            if(j < m + 1){
                A[j][m + 1] += y[i] * x_pow;
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
    double* coef = substituicao(A, m + 1);
    for (int i = 0; i <= m; i++)
    {
        free(A[i]);
    }
    free(A);
    return coef;
}

__declspec(dllexport) void free_memory(void* ptr) {
    free(ptr);
}

__declspec(dllexport) double test_minimo_quadrados(double x, double* coef, int n){
    double pow_x=1;
    double y=0;
    for (int i = 0; i < n; i++) 
    {
        y+=pow_x*coef[i];
        pow_x*=x;
    }
    return y;
}