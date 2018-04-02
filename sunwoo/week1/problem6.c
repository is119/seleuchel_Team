//문제 6번
/*
3, 6, 9 게임을 만들어 보자. 수영, 지후, 하진, 사용자가 369게임을 한다. 박수는 0으로 한다.
사용자가 틀린 답을 입력했을 시, 프로그램이 종료되게 만들자.
1. 박수는 0으로 입력
2. 만약 틀릴 시 프로그램 종료 --> 틀렸을 경우 return 0;

*/

#include<stdio.h>

int main(void) {
	int su_num, jee_num, ha_num;
	int i = 1;//해당 게임의 정답 숫자

	printf("3, 6, 9게임 입니다.\n참여자는 \"수영\", \"지후\", \"하진\" 입니다.\n");


	while (1)
	{
		printf("수영: ");
		scanf_s("%d", &su_num, sizeof(su_num));
		if ((i % 10 != 3) || (i % 10 != 6) || (i % 10 != 9)) {//ex)1,2,4,5,7,8,
			if ((su_num != i) && (su_num != 0)) 
			{
				printf("틀렸습니다. 게임을 종료합니다.\n");
				return 0;
			}
		}
		if ((i % 10 == 3) || (i % 10 == 6) || (i % 10 == 9)) {
			if (su_num != 0)
			{
				printf("틀렸습니다. 게임을 종료합니다\n");
				return 0;
			}
		}
		i++;

		printf("지후: ");
		scanf_s("%d", &jee_num, sizeof(jee_num));
		if ((i % 10 != 3) || (i % 10 != 6) || (i % 10 != 9)) {
			if ((jee_num != i) && (jee_num != 0)) 
			{
				printf("틀렸습니다. 게임을 종료합니다.\n");
				return 0;
			}
		}
		if ((i % 10 == 3) || (i % 10 == 6) || (i % 10 == 9)) {
			if (jee_num != 0)
			{
				printf("틀렸습니다. 게임을 종료합니다\n");
				return 0;
			}
		}
		i++;
		//printf("i의 값은 : %d", i);


		printf("하진: ");
		scanf_s("%d", &ha_num, sizeof(ha_num));
		if ((i % 10 != 3) || (i % 10 != 6) || (i % 10 != 9)) {
			if ((ha_num != i) && (ha_num !=0))
			{
				printf("틀렸습니다. 게임을 종료합니다.\n");
				return 0;
			}
		}

		if ((i % 10 == 3) || (i % 10 == 6) || (i % 10 == 9)) {
			if (ha_num != 0)
			{
				printf("틀렸습니다. 게임을 종료합니다\n");
				return 0;
			}
		}
		i++;

	}


	return 0;

}
