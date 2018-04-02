//// 회문(Palindrome)은 앞으로 읽으나 뒤로 읽으나 차이가 없는 단어들을 말한다. ex)bob, noon 
//// 사용자로부터 단어를 입력 받아 인자로 전달되는 영단어가 회문인지 아닌지를 판단해서 출력하는 프로그램을 만들어보자.
//
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//bool is_Palindrome(char* x);
//
//int main()
//{
//	char word[10];
//
//	printf("Enter a Word : ");
//	scanf_s("%s", word, sizeof(word));
//
//	if (is_Palindrome(word))
//		printf("This word \"%s\" is palindrome!\n", word);
//	else
//		printf("This word  \"%s\" isn't palindrome!\n", word);
//
//	system("pause");
//	return 0;
//}
//
//bool is_Palindrome(char* word)
//{
//	char before[10], after[10];
//
//	for (int j = 0; j < 10; j++)
//	{
//		before[j] = word[j];
//	}
//	for (int i = 0; i < (strlen(word) / 2); i++)
//	{
//		char tmp = word[i];
//		word[i] = word[strlen(word) - 1 - i];
//		word[strlen(word) - 1 - i] = tmp;
//	}
//	for (int k = 0; k < 10; k++)
//	{
//		after[k] = word[k];
//	}
//
//	if (strcmp(before, after) == 0)
//		return true;
//	else
//		return false;
//}