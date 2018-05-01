#include <stdio.h>
#include <string.h>


struct Tank {
	char name[100];
	char phone[100];
	int number;
};

int main(void)

{
	struct Tank A[100];
	int t = 0;
	int a = 0;
	
	// A 초기화
	for (int t = 0 ; t <= 100; t++)
	{
		strcpy_s(A[t].name, sizeof(A[t].name),"");
		strcpy_s(A[t].phone, sizeof(A[t].phone),"");
		A[t].number = 0;
	}

	while (1) {
	Loop:

		printf_s("1번과 2번중 고르시오!! \n");
		printf_s("1번: 번호 저장  2번 번호 찾기\n");
		scanf_s("%d", &a);

		if (a == 1)
		{

			while (t <= 100)
			{
				printf_s("이름 입력 : ");
				scanf_s("%s", &A[t].name, sizeof(A[t].name));
				printf_s("핸드폰 번호를 입력: ");
				scanf_s(" %s", &A[t].phone, sizeof(A[t].phone));
				printf_s("학번을 입력 : ");
				scanf_s(" %d", &A[t].number, sizeof(A[t].number));

				t++;
				goto Loop;
			}
		}
		else if (a == 2)
		{

			int b = 0;

			for (int i = 0; i <= 100; i++)
			{
				if (A[i].number != 0)
				{
					printf_s("%d ", i);
					printf(" %s\n", A[i].name);
				}
			}
			printf_s("원하는 사람의 번호를 입력해주세요! \n");
			scanf_s(" %d", &b);
			printf_s("%s\n", A[b].name);
			printf_s("%s\n", A[b].phone);
			printf_s("%d\n", A[b].number);

		}
	}
	return 0;
}




