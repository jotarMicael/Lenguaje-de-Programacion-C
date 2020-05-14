#include <stdio.h>
int main()
{

const char* dias[7] = {
"Lunes", "Martes", "Miercoles", "Jueves",
"Viernes", "Sabado", "Domingo"};

int i;
	for (i = 0; i < 7; i++)
	printf("%.3s\t",dias[i]);

for (i = 1; i <= 31; i++) {
	if (!((i - 1) % 7))
		printf("\n");
	printf("%d\t",i);
}
	printf("\n");
	return 0;
}