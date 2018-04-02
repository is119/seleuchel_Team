//문제 1번
/*
10진수를 입력 받았을 때, 이를 8진수와 16진수로 출력하는 프로그램을 작성하라. 
*/

#include<stdio.h>

int main(void)
{	
	int number, number4hex;
	int oct, hex;
	int sum = 0;
	int position = 1;//자리수 구분
	char hexadecimal[15] = { 0, };



	printf("10진수 입력: ");
	scanf_s("%ld", &number);
	
	number4hex = number;//16진수 변환을 위해
	//8진수 변환 알고리즘
	while (number > 0)
	{
		oct = number % 8;
		sum += oct * position;
		number /= 8;
		position *= 10;//shift
	}
	
	printf("8진수: %ld\n", sum);
	

	
	//16진수 변환 알고리즘
	position = 0;//여기선 자리배가 배열로 들어가므로
	while (number4hex > 0)
	{
		hex = number4hex % 16;
		
		//ASCII코드 이용 1-9, A-F모두 문자로 표시
		if (hex < 10) {
			hexadecimal[position] = 48 + hex;
		}
		else {//A,B,C,D,E,F일 경우
			hexadecimal[position] = 65 + (hex - 10);
		}

		number4hex /= 16;
		position++;
	}
	printf("16진수: ");
	for (int i = position - 1; i >= 0; i--)
	{
		printf("%c", hexadecimal[i]);
	}
	printf("\n");


		return 0;
}
