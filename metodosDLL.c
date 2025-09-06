#include <stdbool.h>
#include <math.h>

__declspec(dllexport) double f1(double x) {
    return (x*x)-2;
}

__declspec(dllexport) double d1(double x){
    return 2*x;
}

__declspec(dllexport) double f2(double x) {
    return (x*x*x)-x-2;
}

__declspec(dllexport) double d2(double x){
    return 3*(x*x)-1;
}

__declspec(dllexport) double f3(double x) {
    return (x*x*x*x*x)-x-1;
}

__declspec(dllexport) double d3(double x) {
    return 5*(x*x*x*x)-1;
}

__declspec(dllexport) double f4(double x) {
    return cos(x) - x;
}

__declspec(dllexport) double d4(double x) {
    return -sin(x) - 1;
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