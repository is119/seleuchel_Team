// 3, 6, 9 게임을 만들어 보자. 수영, 지후, 하진, 사용자가 369게임을 한다. 박수는 0으로 한다. 사용자가 틀린 답을 입력했을 시, 프로그램이 종료되게 만들자.

#include <stdio.h>

int rightanswer(int count);

int main()
{
	int count = 1;

	printf("***** 369게임 *****\n");
	printf("플레이어 : 수영, 지후, 하진, user\n");
	printf("게임 룰 : 기존의 369와 같지만 박수는 33이든 3이든 '0'으로 표현한다!\n");

	while (1)
	{
		int userchoice = 0;

		if (count >= 100)
		{
			printf("숫자가 너무 큽니다.");
			system("pause");
			return 0;
		}

		switch (count % 4)
		{
			case 0: 
				printf("user : ");
				break;
			case 1:
				printf("수영 : ");
				break;
			case 2:
				printf("지후 : ");
				break;
			case 3: 
				printf("하진 : ");
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
	count -= tmp_10 * 10; // 일의 자리수를 얻기 위해 십의 자리수 제거 작업
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
