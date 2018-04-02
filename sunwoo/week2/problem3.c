/*
길이가 5인 int형 배열을 선언해서 프로그램 사용자로부터 총 5개의 정수를 입력 받자. 그리고 입력된 정수 중에서 최댓값, 최솟값을 출력하도록 해보자.
 1. 길이가 5인 int배열
 2. 사용자로부터 5개의 정수 입력 받음
 3. 그 중 최댓값, 최솟값 출력
*/

#include<stdio.h>

int main(void)
{
	int biggest, smallest;
	//int array[5];
	int array[6];//index에러 떠서 크기 1만큼 증가시킴.
	int* array_ptr = array;//예외가 떠서 포인터로 처리, 시작 주소는 array[0]
	printf("5개의 정수를 입력할 수 있습니다.\n");

	//정수 입력 --> 5개
	for (int i = 0; i < 5; i++)
	{
		printf("정수 입력: ");
		scanf_s("%d", (array_ptr + i*4) );
	}

	//최댓값 
	biggest = *(array_ptr);
	for (int i = 1; i < 5; i++)
	{
		if ( *(array_ptr + i*4) > biggest)
			biggest = *(array_ptr + i*4);
	}
	
	//최솟값
	smallest = *(array_ptr);
	for (int i = 1; i < 5; i++)
	{
		if ( *(array_ptr + i*4) < smallest)
			smallest = *(array_ptr + i*4);
	}

	printf("최댓값: %d\n최솟값: %d\n", biggest, smallest);

	return 0;
}
