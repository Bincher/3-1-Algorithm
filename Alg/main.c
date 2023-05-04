#include <stdio.h>
#include <math.h>

void main()
{
	int item[4][2] =
	{
		{10, 5},
		{40, 4},
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
			if (item[i - 1][1] > w)
				K[i][w] = K[i - 1][w];
			else
				if (K[i - 1][w] > K[i - 1][w - item[i - 1][1]] + item[i - 1][0])
					K[i][w] = K[i - 1][w];
				else
					K[i][w] = K[i - 1][w - item[i - 1][1]] + item[i - 1][0];
			
		}
	}

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= C; j++)
		{
			printf("%d ", K[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}