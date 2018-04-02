//// 영단어를 입력 받아서 char형 배열에 저장한다. 그 다음 배열에 저장된 영단어를 역순으로 뒤집고, 출력을 통해 확인해 보자. (단, null 문자의 위치를 변경하면 안 된다.)
//
//#include <stdio.h>
//#include <string.h>
//
//int main()
//{
//	char word[10];
//	printf("Enter a word : ");
//	scanf_s("%s", word, sizeof(word));
//
//	for (int i = 0; i < (strlen(word) / 2); i++)
//	{
//		char tmp = word[i];
//		word[i] = word[strlen(word) - 1 - i];
//		word[strlen(word) - 1 - i] = tmp;
//	}
//
//	printf("%s\n", word);
//
//	system("pause");
//	return 0;
//}