/*
회문(Palindrome)은 앞으로 읽으나 뒤로 읽으나 차이가 없는 단어들을 말한다. ex)bob, noon
사용자로부터 단어를 입력 받아 인자로 전달되는 영단어가 회문인지 아닌지를 판단해서 출력하는 프로그램을 만들어보자.
*/

#define _CRT_SECURE_NO_WARNINGS //scanf_s의 경우, printf로 ptr4sentence를 출력하자, 외계어가 발생. 따라서, scanf로 사용하기 위해 선언해준 define
#include<stdio.h>
#include<string.h>


int main(void)
{
	int isPal = 1;//True일 경우 1, False일 경우 0
	char* ptr4sentence = malloc(sizeof(char) * 100);
	
	printf("회문인지 판단하여, 회문일 경우 회문을 출력해주는 프로그램입니다.\n");
	printf("문자 입력: ");


	//영문 입력만 허용합니다. 한글 회문판단은 지원 안함.	
	scanf("%s", ptr4sentence);
	
	//회문 판단
	for (int i = 0; i < strlen(ptr4sentence) / 2; i++)
	{
		if (ptr4sentence[i] != ptr4sentence[strlen(ptr4sentence) - 1 - i])
		{
			//회문 아님
			isPal = 0;//false
			break;
		}
	}

	//회문 판단
	if (isPal == 1)
		printf("회문 O\n");
	else
		printf("회문 X\n");

	free(ptr4sentence);
	return 0;
}
