/*
Int형 변수인 n1, n2을 선언해 각각 값을 저장한 뒤, n1과 n2에 저장된 값을 서로 뒤바꾸는 함수를 정의하고 정상적으로 함수가 작동하는지 출력 해보자.
*/

#include<stdio.h>

void swap(int n1, int n2);

int main(void)
{
	int n1, n2;
	n1 = 10;
	n2 = 5;
	
	printf("swap전\nn1: %d\nn2: %d\n", n1, n2);
	swap(n1, n2);
	printf("\n\nswap후\nn1: %d\nn2 : %d\n", n1, n2);

	return 0;
}

void swap(int n1, int n2)
{
	int temp;//buffer역할
	temp = n2;
	n2 = n1;
	n1 = temp;
}
