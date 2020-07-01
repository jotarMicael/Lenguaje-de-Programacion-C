#include <stdio.h>

#define macro1(expr) printf(#expr "= %g\n", expr);
#define macro2(uno,dos) (uno ## dos);


int main(){

double s = 10.5;

macro2(s,s);



}