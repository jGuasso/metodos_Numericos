<h1>Implementações da disciplina de Métodos Numéricos Computacionais</h1>
Esse repositório contém implementações em C e em casos que a visualização gráfica é necessária, os métodos são compilados em uma DLL, e utilizados em um Jupyter Notebook.
<h3>Compilar DLL</h3>
<code>gcc -shared -o metodos.dll -fPIC .\metodosDLL.c -lm</code>