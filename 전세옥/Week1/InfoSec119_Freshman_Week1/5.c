//// ���Ǳ⸦ ����� ����.���Ǳ� �� ������� �ݶ�, ���̴�, ȯŸ �� ������ �ִ�.���� �ݾ��� �Է��� ��, ���ϴ� ���� ��ŭ�� ������� �̰� ���� �Ž������� �������� ��ȯ�Ѵ�.
//#include <stdio.h>
//
//int main()
//{
//	while (1)
//	{
//		int Selection = 0, NumberOfSoda = 0, InputMoney = 0, Price = 0;
//		printf("���� ����� ���Ǳ� �Դϴ�.\n");
//		printf("����\n (1)�ݶ�[1200��]\n (2)���̴�[1000��]\n (3)ȯŸ[800��]\n (4)����\n");
//		printf("���ϴ� ���Ḧ �����ϼ��� : ");
//		scanf_s("%d", &Selection);
//
//		if (Selection == 4)
//			break;
//
//		if (Selection < 1 || Selection > 4)
//		{
//			printf("�߸��� �Է��Դϴ�. �ý����� �����մϴ�!!\n");
//			system("pause");
//			return 0;
//		}
//
//		printf("���Ͻô� ������ �Է����ּ��� : ");
//		scanf_s("%d", &NumberOfSoda);
//
//		printf("���� ������ �ּ��� : ");
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
//			printf("���� �����մϴ�. ó������ �ٽ� �Է����ּ���!\n");
//		else
//		{
//			int TmpChange = 0, Change_500, Change_100;
//			TmpChange = InputMoney - Price;
//			Change_500 = TmpChange / 500;
//			TmpChange -= (Change_500 * 500);
//			Change_100 = TmpChange / 100;
//			printf("�Ž������� 500��¥�� %d��, 100�� ¥�� %d���Դϴ�.\n\n\n", Change_500, Change_100);
//		}
//			
//	}
//
//	system("pause");
//	return 0;
//}