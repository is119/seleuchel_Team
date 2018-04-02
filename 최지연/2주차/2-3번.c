#include <stdio.h>

int main(void)
{
	int num[5];
	int min, max, i;
	
	for (i = 0; i < 5; i++)
	{
		printf("Á¤¼öÀÔ·Â: ");
		scanf("%d", &num[i]);
	}

	min = max = num[0];
	for (i = 1; i < 5; i++)
	{
		if (min > num[i])
			min = num[i];
		if (max < num[i])
			max = num[i];
	}

	printf("ÃÖ¼Ú°ª: %d \n", min);
	printf("ÃÖ´ñ°ª: %d \n", max);
	return 0;
}