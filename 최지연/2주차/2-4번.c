#include <stdio.h>

int main(void)
{
	char word[50];
	int num = 0, i;
	char temp;

	printf("���ܾ� �Է�: ");
	scanf("%s", word);

	while (word[num] != '\0')
		num++;
	for (i = 0; i < num / 2; i++)
	{
		temp = word[i];
		word[i] = word[(num - i) - 1];
		word[(num - i) - 1] = temp;
	}
	printf("������ ���ܾ�: %s \n", word);
	return 0;
}