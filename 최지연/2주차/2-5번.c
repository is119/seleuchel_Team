#include <stdio.h>

int main(void)
{
	char word[50];
	int num = 0, i;
	char temp;
	char origin = word;

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
	if (word == origin)
		printf("ȸ���̴�. \n");
	else
		printf("ȸ���� �ƴϴ�. \n");
	return 0;
}