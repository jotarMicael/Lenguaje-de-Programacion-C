#include <stdio.h>

int suma(int numero){

int sumatoria;

sumatoria=0;

while (numero>0)
{

sumatoria=(sumatoria+numero);

numero--;

}

return sumatoria;

}