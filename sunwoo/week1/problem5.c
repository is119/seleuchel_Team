//문제 5번
/*
자판기를 만들어 보자. 
자판기 내 음료수는 콜라, 사이다, 환타 세 종류가 있다. 
넣을 금액을 입력한 후, 원하는 개수 만큼의 음료수를 뽑고 남은 거스름돈은 동전으로 반환한다.
*/

#include<stdio.h>

int main(void) 
{	
	int inputcoin,pluscoin;
	int choice;
	int coke = 0;
	int sprite = 0;
	int fanta = 0;
	int count;
	printf("자판기 프로그램입니다.\n====================\n==  콜라   700원  ==\n==  사이다 700원  ==\n==  환타   800원  ==\n====================\n");
	printf("투입 금액: ");
	scanf_s("%d", &inputcoin, sizeof(inputcoin));

	while (1) {
		printf("뽑으실 음료수를 골라주세요. \n콜라:1/사이다/2/환타3\/다 골랐다4\n선택:");
		scanf_s("%d", &choice, sizeof(choice));
	
		
			
			if (choice == 1) {
				printf("개수 입력: ");
				scanf_s("%d", &count, sizeof(count));
				
				if (inputcoin < count * 700) {
					while(inputcoin < count *700){
					printf("\t돈이 부족합니다. 돈을 더 넣어주세요.\n");
					printf("\t추가 금액 투입: ");
					scanf_s("%d", &pluscoin, sizeof(pluscoin));

					inputcoin += pluscoin;
					}
				}
				
				coke = count;
				
				inputcoin -= coke*700;
				printf("콜라 %d개, 총 %d원만큼 고르셨습니다. 남은 금액은 %d원입니다.\n\n\n", coke, coke * 700, inputcoin);
			}

			if (choice == 2) {
				printf("개수 입력: ");
				scanf_s("%d", &count, sizeof(count));
				
				if (inputcoin < count * 700) {
					while (inputcoin < count * 700) {
						printf("\t돈이 부족합니다. 돈을 더 넣어주세요.\n");
						printf("\t추가 금액 투입: ");
						scanf_s("%d", &pluscoin, sizeof(pluscoin));

						inputcoin += pluscoin;
					}
				}

				sprite = count;

				inputcoin -= sprite*700;
				printf("콜라 %d개, 총 %d원만큼 고르셨습니다. 남은 금액은 %d원입니다.\n\n", sprite, sprite * 700, inputcoin);
			}

			if (choice == 3) {
				printf("개수 입력: ");
				scanf_s("%d", &count, sizeof(count));
				
				if (inputcoin < count * 700) {
					while (inputcoin < count * 700) {
						printf("\t돈이 부족합니다. 돈을 더 넣어주세요.\n");
						printf("\t추가 금액 투입: ");
						scanf_s("%d", &pluscoin, sizeof(pluscoin));

						inputcoin += pluscoin;
					}
				}
				fanta = count;

				inputcoin -= fanta*800;
				printf("콜라 %d개, 총 %d원만큼 고르셨습니다. 남은 금액은 %d원입니다.\n\n", sprite, sprite * 700, inputcoin);

			}
		
			if (choice == 4) {
				printf("\n\n===========================================================");
				printf("\n콜라: %d개, 사이다: %d개, 환타: %d개 만큼 구입하셨습니다.\n", coke, sprite, fanta);
				printf("총 소비금액은 %d원 입니다.\n", coke * 700 + sprite * 700 + fanta * 800);
				printf("거스름돈은 %d원 입니다.\n\n", inputcoin);
				printf("===========================================================\n\n");

				return 0;
			}

	}
	
	return 0;
}

