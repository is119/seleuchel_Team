#include <stdio.h>

double CtoF(double c)
{
	return 1.8*c + 32;
}

int main(void)
{
	double num;
	printf("¼·¾¾ ÀÔ·Â : ");
	scanf("%lf", &num);
	printf("º¯È­µÈ È­¾¾ : %f \n", CtoF(num));

	return 0;
}