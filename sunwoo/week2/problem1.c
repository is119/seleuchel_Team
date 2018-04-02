
/*
problem1. 섭씨온도를 입력 받아 화씨로 변환하여 출력하는 함수를 정의하고, 호출하여 실행해 보자.
섭씨 :C / 화씨 :F라고 할때,
F = C * 1.8 +32
*/

#include<stdio.h>

int main(void)
{
	double celcius;
	printf("섭씨 --> 화씨 변환 프로그램\n");
	printf("온도 입력(섭씨): ");
	scanf_s("%lf", &celcius);

	printf("온도(화씨): %lf\n" , celcius *1.8 + 32);
	

	return 0;
}
