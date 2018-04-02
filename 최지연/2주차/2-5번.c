#include <stdio.h>

int main(void)
{
	char word[50];
	int num = 0, i;
	char temp;
	char origin = word;

	printf("영단어 입력: ");
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
		printf("회문이다. \n");
	else
		printf("회문이 아니다. \n");
	return 0;
}