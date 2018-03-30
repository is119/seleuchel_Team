//// 10미만의 자연수에서 3과 5의 배수를 구하면 3,5,6,9이다. 이들의 총합은 23이다.
//// 1000미만의 자연수에서 3, 5의 배수의 총합을 구하라.
//
//#include <stdio.h>
//
//int main()
//{
//	int result = 0;
//	int NumberOfPentas = (1000 / 5) - 1; // 1을 빼는 이유는 1000도 5의 배수가 되기 때문이다.
//	int NumberOfTriples = (1000 / 3);
//
//	while (NumberOfPentas != 0)
//	{
//		result += NumberOfPentas * 5;
//		NumberOfPentas--;
//	}
//
//	while (NumberOfTriples != 0)
//	{
//		result += NumberOfTriples * 3;
//		NumberOfTriples--;
//	}
//
//	printf("1000미만의 자연수에서 3, 5의 배수의 총합은 %d 입니다!!\n", result);
//	system("pause");
//	return 0;
//}