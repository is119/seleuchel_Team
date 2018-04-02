/*
영단어를 입력 받아서 char형 배열에 저장한다. 그 다음 배열에 저장된 영단어를 역순으로 뒤집고, 출력을 통해 확인해 보자.
(단, null 문자의 위치를 변경하면 안 된다.)--> 마지막은 고정인듯.

*/

#define _CRT_SECURE_NO_WARNINGS //scanf_s의 경우, printf로 ptr4sentence를 출력하자, 외계어가 발생. 따라서, scanf로 사용하기 위해 선언해준 define
#include<stdio.h>
#include<string.h>

int main(void)
{
	int i = 0;
	int length;
	//char sentence[300] = {0,};//배열은 상수, 포인터는 변수
	char* ptr4sentence = malloc(sizeof(char) * 100);
	
	printf("문자를 거꾸로 출력해주는 프로그램입니다.\n");
	printf("문자 입력: ");

	//문자 입력된 길이를 아는게 관건
	scanf("%s", ptr4sentence);
	printf("원문: %s\n", ptr4sentence);
	
	//역순 문자열 출력
	printf("역순: ");
	for (int i = strlen(ptr4sentence)-1; i >= 0; i--)
		{
		printf("%c", *(ptr4sentence + i));
		}
	printf("\n");


	free(ptr4sentence);
	return 0;
}
