//// ���ܾ �Է� �޾Ƽ� char�� �迭�� �����Ѵ�. �� ���� �迭�� ����� ���ܾ �������� ������, ����� ���� Ȯ���� ����. (��, null ������ ��ġ�� �����ϸ� �� �ȴ�.)
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