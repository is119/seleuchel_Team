//// 자판기를 만들어 보자.자판기 내 음료수는 콜라, 사이다, 환타 세 종류가 있다.넣을 금액을 입력한 후, 원하는 개수 만큼의 음료수를 뽑고 남은 거스름돈은 동전으로 반환한다.
//#include <stdio.h>
//
//int main()
//{
//	while (1)
//	{
//		int Selection = 0, NumberOfSoda = 0, InputMoney = 0, Price = 0;
//		printf("전컴 음료수 자판기 입니다.\n");
//		printf("종류\n (1)콜라[1200원]\n (2)사이다[1000원]\n (3)환타[800원]\n (4)종료\n");
//		printf("원하는 음료를 선택하세요 : ");
//		scanf_s("%d", &Selection);
//
//		if (Selection == 4)
//			break;
//
//		if (Selection < 1 || Selection > 4)
//		{
//			printf("잘못된 입력입니다. 시스템을 종료합니다!!\n");
//			system("pause");
//			return 0;
//		}
//
//		printf("원하시는 개수를 입력해주세요 : ");
//		scanf_s("%d", &NumberOfSoda);
//
//		printf("돈을 지급해 주세요 : ");
//		scanf_s("%d", &InputMoney);
//
//
//		switch (Selection)
//		{
//		case 1:
//			Price = NumberOfSoda * 1200;
//			break;
//		case 2:
//			Price = NumberOfSoda * 1000;
//			break;
//		case 3:
//			Price = NumberOfSoda * 800;
//			break;
//		}
//
//		if (Price > InputMoney)
//			printf("돈이 부족합니다. 처음부터 다시 입력해주세요!\n");
//		else
//		{
//			int TmpChange = 0, Change_500, Change_100;
//			TmpChange = InputMoney - Price;
//			Change_500 = TmpChange / 500;
//			TmpChange -= (Change_500 * 500);
//			Change_100 = TmpChange / 100;
//			printf("거스름돈은 500원짜리 %d개, 100원 짜리 %d개입니다.\n\n\n", Change_500, Change_100);
//		}
//			
//	}
//
//	system("pause");
//	return 0;
//}