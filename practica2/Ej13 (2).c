#include <stdio.h>


#define START  0  /* Punto de comienzo del bucle */
 
#define ENDING 9  /* Punto de final del bucle */
 
#define MAX(A,B)  ((A)>(B)?(A):(B))  /* Macro definitoria de Max */
 
#define MIN(A,B)  ((A)>(B)?(B):(A))  /* Macro definitoria de Min */
 

 
int main()
 
{
 
int index,mn,mx;
 
int count = 5;
 
for (index = START;index <= ENDING;index++) {
 
mx = MAX(index++,count++);
 
mn = MIN(index++,count++);
 
printf("Max es %d y min es %d\n",mx,mn);
 
}
 
}
 