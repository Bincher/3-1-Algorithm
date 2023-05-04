#include <stdio.h>
#include <math.h>


void main()
{
	// C와 n 그리고 item 크기 변경 유동적으로
	// K가 문제
	// DISPLAY 좀 더 신경쓰고
	int item[4][2] =
	{
		{10, 5},
		{20, 4},
		{30, 6},
		{50, 3}
	}; // 가치, 무게
	int n = (int)(sizeof(item) / sizeof(item[0])); // 아이템 수
	int C = 10; // 배낭 무게 한계
	int K[5][11]; 
	
	for (int i = 0; i <= n; i++)
		K[i][0] = 0;
	for (int w = 0; w <= C; w++)
		K[0][w] = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int w = 1; w <= C; w++)
		{
			printf("K[%d,%d]:", i, w);
			if (item[i - 1][1] > w)
			{
				K[i][w] = K[i - 1][w];
				printf("%d ■ ", K[i][w]);
			}
			else
			{
				if (K[i - 1][w] > K[i - 1][w - item[i - 1][1]] + item[i - 1][0])
				{
					K[i][w] = K[i - 1][w];
				}
				else
				{
					K[i][w] = K[i - 1][w - item[i - 1][1]] + item[i - 1][0];
				}
				printf("max{%d,%d} = %d ■ ", K[i - 1][w], K[i - 1][w - item[i - 1][1]] + item[i - 1][0], K[i][w]);
			}
		}
		printf("\n");
	}
	
	printf("결과\n");
	printf("――――――――――――――――――――――――――――――――――――――――――――――――――\n");
	for (int i = 0; i <= n + 1; i++)
	{
		for (int j = 0; j <= C + 1; j++)
		{
			if (i == 0)
				if (j == 0)
					printf("|용량|");
				else
					printf("%3d|", j - 1);
			else
				if (j == 0)
				{
					if (i == 1)
					{
						printf("|물건|");
					}
					else
						printf("|i=%d |", i - 1);
				}
				else 
					printf("%3d|", K[i - 1][j - 1]);
		}
		printf("\n");
		printf("――――――――――――――――――――――――――――――――――――――――――――――――――\n");
	}
	printf("\n");
}