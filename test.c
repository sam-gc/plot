#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Starting malloc\n");
	int i;
	for(i = 0; i < 4; i++)
	{
		double *test = malloc(sizeof(double) * 600);
	}
	printf("Ending malloc\n");
}