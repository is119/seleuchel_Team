// 3, 6, 9 ������ ����� ����. ����, ����, ����, ����ڰ� 369������ �Ѵ�. �ڼ��� 0���� �Ѵ�. ����ڰ� Ʋ�� ���� �Է����� ��, ���α׷��� ����ǰ� ������.

#include <stdio.h>

int rightanswer(int count);

int main()
{
	int count = 1;

	printf("***** 369���� *****\n");
	printf("�÷��̾� : ����, ����, ����, user\n");
	printf("���� �� : ������ 369�� ������ �ڼ��� 33�̵� 3�̵� '0'���� ǥ���Ѵ�!\n");

	while (1)
	{
		int userchoice = 0;

		if (count >= 100)
		{
			printf("���ڰ� �ʹ� Ů�ϴ�.");
			system("pause");
			return 0;
		}

		switch (count % 4)
		{
			case 0: 
				printf("user : ");
				break;
			case 1:
				printf("���� : ");
				break;
			case 2:
				printf("���� : ");
				break;
			case 3: 
				printf("���� : ");
				break;
		}

		if ((count % 4) == 0)
		{
			scanf_s("%d", &userchoice);
			if (userchoice != rightanswer(count))
			{
				system("pause");
				return 0;
			}
		}
		else
			printf("%d\n", rightanswer(count));

		count++;
	}
	system("pause");
	return 0;
}

int rightanswer(int count)
{
	int tmp_10, tmp_1, result = 0;
	
	tmp_10 = count / 10;
	count -= tmp_10 * 10; // ���� �ڸ����� ��� ���� ���� �ڸ��� ���� �۾�
	tmp_1 = count;

	switch (tmp_10)
	{
	case 0:
		break;
	case 3:
	case 6:
	case 9:
		return result = 0;
	default:
		result = tmp_10 * 10;
	}

	switch (tmp_1)
	{
	case 3:
	case 6:
	case 9:
		return result = 0;
	default:
		result += tmp_1;
	}

	return result;
}
