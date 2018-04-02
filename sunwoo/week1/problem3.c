//문제 3번
/*
사용자로부터 정수 n을 입력 받았을 때, 그 정수의 계승(factorial)을 계산하고 출력하는 프로그램을 작성하라.
*/

#include<stdio.h>

int main(void) {
	int inputnum,result;
	printf("factorial을 계산하여 출력하는 프로그램입니다.\n");
	printf("수 입력: ");
	scanf_s("%d", &inputnum, sizeof(inputnum));
	
	if (inputnum == 0) {
		printf("!%d = 0\n", inputnum);
		return 0;
	}

	if (inputnum != 0) {
		result = 1;
		for (int i = inputnum; i > 0; i--) {
			result *= i;
		}
	}
	printf("!%d = %d\n", inputnum, result);

	return 0;
}
