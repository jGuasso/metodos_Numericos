#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

/* ============================================= */
/* FUNÇÕES EXISTENTES (ZEROS)           */
/* ============================================= */

__declspec(dllexport) double f1(double x) {
    return (x*x)-2;
}

__declspec(dllexport) double d1(double x){
    return 2*x;
}

/* Método da Bisseção */
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

/* Método da Falsa Posição */
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

/* Newton-Raphson */
__declspec(dllexport) double newton_raphson(double(*funcao)(double),double(*derivada)(double),double x,double epsilon){
    while (fabs(funcao(x))>epsilon)
    {
        x = x - funcao(x)/derivada(x);
    }
    return x;
}

/* Método das Secantes */
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


/* ============================================= */
/* FUNÇÕES EXISTENTES (AJUSTE CURVA)        */
/* ============================================= */

/* Funções auxiliares (trocaLinhas, escalonamento, substituicao) */
/* (Usadas por minimos_quadrados) */
void trocaLinhas(double **l1,double **l2){
    double *temp = *l1;
    *l1 = *l2;
    *l2 = temp;
}

void escalonamento(double **m, int n){ // Eliminação de Gauss

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

double* substituicao(double **m, int n){ // Substituição retroativa
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

    // Inicializa A com zeros (importante!)
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= m + 1; j++){
            A[i][j] = 0.0;
        }
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
    
    escalonamento(A, m + 1); // Eliminação de Gauss
    double* coef = substituicao(A, m + 1); // Substituição retroativa
    
    for (int i = 0; i <= m; i++)
    {
        free(A[i]);
    }
    free(A);
    return coef;
}

__declspec(dllexport) double test_minimo_quadrados(double x, double* coef, int n_coeffs){
    double pow_x=1;
    double y=0;
    // 'n_coeffs' é o número de coeficientes (grau + 1)
    for (int i = 0; i < n_coeffs; i++) 
    {
        y+=pow_x*coef[i];
        pow_x*=x;
    }
    return y;
}

/* ============================================= */
/* FUNÇÕES NOVAS (INTERPOLAÇÃO)        */
/* ============================================= */

/* --- Funções Auxiliares (Interpolação por Definição) --- */

// Escalonamento Gauss-Jordan (diferente do 'escalonamento' acima)
// Não é 'dllexport' pois é apenas usada internamente por 'interpolacao_definicao_coeffs'
static double* escalonamento_gj(double **m, int n){
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
            
            double d = m[j][i]/m[i][i]; // m[i][i] é 1, mas mantido por robustez
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


/* --- 1. Interpolação por Definição (Sistema Linear) --- */

__declspec(dllexport) double* interpolacao_definicao_coeffs(int n, double* x_arr, double* y_arr){
    // 1. Cria matriz A
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

    // 2. Resolve sistema
    double *a = escalonamento_gj(A, n);

    // 3. Libera matriz A
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    // 4. Retorna coeficientes
    return a;
}

__declspec(dllexport) double calcula_polinomio(double x, double* a_coeffs, int n){
    double xpow=1;
    double r=0;
    for (int i = 0; i < n; i++)
    {
        r+=a_coeffs[i]*xpow;
        xpow*=x;
    }
    return r;
}


/* --- 2. Interpolação de Lagrange --- */

__declspec(dllexport) double* lagrange_cria_polinomio(const int n, const double *x_arr, const double *y_arr){
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

__declspec(dllexport) double lagrange_resulta_polinomio(const double x, const double *coef, const double *x_arr, const int n){
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

/* --- 3. Interpolação de Newton --- */

__declspec(dllexport) double* coeficientes_newton(int n, double* x_arr, double* y_arr){
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
    
    // Copia coeficientes (tabela[0]) para um novo array
    double* coef = (double*)malloc(sizeof(double)*n);
    for(int i=0; i<n; i++){
        coef[i] = tabela[0][i];
    }

    // Libera a tabela temporária
    for(int i=0; i<n; i++){
        free(tabela[i]);
    }
    free(tabela);

    return coef; // Retorna os coeficientes
}

__declspec(dllexport) double interpolacao_newton(int n, double* x_arr, double* coef, double x){
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


/* ============================================= */
/* FUNÇÃO DE LIMPEZA              */
/* ============================================= */

__declspec(dllexport) void free_memory(void* ptr) {
    free(ptr);
}