//// 길이가 5인 int형 배열을 선언해서 프로그램 사용자로부터 총 5개의 정수를 입력 받자. 그리고 입력된 정수 중에서 최댓값, 최솟값을 출력하도록 해보자.
//
//#include<stdio.h>
//
//int Max(int* a);
//int Min(int* a);
//
//int main()
//{
//	int a[5];
//	for (int i = 0; i < 5; i++)
//	{
//		printf("Enter integer (number : %d) : ", i);
//		scanf_s("%d", &a[i]);
//	}
//
//	printf("The maximum value is %d\n", Max(a));
//	printf("The minimum value is %d\n", Min(a));
//
//	system("pause");
//	return 0;
//
//}
//int Max(int* a)
//{
//	int maximum = a[0];
//	for (int i = 1; i < 5; i++)
//	{
//		if (maximum >= a[i])
//			maximum = a[i];
//	}
//	return maximum;
//}
//
//int Min(int* a)
//{
//	int minimum = a[0];
//	for (int i = 1; i < 5; i++)
//	{
//		if (minimum <= a[i])
//			minimum = a[i];
//	}
//	return minimum;
//}