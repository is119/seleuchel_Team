//// ȸ��(Palindrome)�� ������ ������ �ڷ� ������ ���̰� ���� �ܾ���� ���Ѵ�. ex)bob, noon 
//// ����ڷκ��� �ܾ �Է� �޾� ���ڷ� ���޵Ǵ� ���ܾ ȸ������ �ƴ����� �Ǵ��ؼ� ����ϴ� ���α׷��� ������.
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