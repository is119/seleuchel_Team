#include <stdio.h>

void main(int n1, int n2)
{
	int num1;
	int num2;
	n1 = 0;
	n2 = 1;
	num1 = n2, num2 = n1;
	printf("n1 , n2 : %d , %d \n", num1, num2);
}