//문제 2번
/*
1단 부터 19단 까지를 출력하는 구구단 프로그램을 작성해 보라.
*/

#include<stdio.h>
int main(void) {
	printf("1단 부터 19단까지 구구단을 출력하는 프로그램입니다.\n");
	
	for (int first = 1; first < 20; first++) 
	{
		printf("%d단\n", first);
		for (int last = 1; last < 20; last++)
		{
			printf("%d * %d = %d\t", first, last, first*last);
			}
		
		printf("\n\n");
	}

	return 0;
}
