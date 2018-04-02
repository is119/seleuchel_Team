//문제 4번 
/*
10미만의 자연수에서 3과 5의 배수를 구하면 3,5,6,9이다. 이들의 총합은 23이다.
1000미만의 자연수에서 3,5의 배수의 총합을 구하라.
*/

#include<stdio.h>

int main(void)
{
	int inputnum;
	printf("x값보다 작은 자연수 중, 3과 5의 배수를 출력해주는 프로그램입니다.\n");
	printf("x값 입력: ");
	scanf_s("%d", &inputnum, sizeof(inputnum));

	//공배수는 어떻게 처리할지 생각...--> if절 or로 처리
	for (int num = 1; num < inputnum; num++) {
		if((num %3 == 0) || (num % 5 == 0))
			printf("%d ",num);
		}
	
	printf("\n");

	return 0;
}
