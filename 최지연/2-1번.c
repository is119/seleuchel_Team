#include <stdio.h>

double CtoF(double c)
{
	return 1.8*c + 32;
}

int main(void)
{
	double num;
	printf("���� �Է� : ");
	scanf("%lf", &num);
	printf("��ȭ�� ȭ�� : %f \n", CtoF(num));

	return 0;
}