#include <stdio.h>
#include <math.h>

void main()
{
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

    // 초기화
    for (int i = 0; i <= n; i++)
        K[i][0] = 0;
    for (int w = 0; w <= C; w++)
        K[0][w] = 0;

    // 0-1 배낭문제 해결을 위한 DP 알고리즘
    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= C; w++)
        {
            printf("K[%d,%d]:", i, w);
            if (item[i - 1][1] > w) // 현재 아이템이 배낭 용량보다 큰 경우
            {
                K[i][w] = K[i - 1][w]; // 이전 아이템에서 얻은 최대 가치를 저장
                printf("%d | ", K[i][w]);
            }
            else // 현재 아이템이 배낭 용량보다 작거나 같은 경우
            {
                if (K[i - 1][w] > K[i - 1][w - item[i - 1][1]] + item[i - 1][0])
                {
                    K[i][w] = K[i - 1][w]; // 현재 아이템을 넣지 않는 경우
                }
                else
                {
                    K[i][w] = K[i - 1][w - item[i - 1][1]] + item[i - 1][0]; // 현재 아이템을 넣는 경우
                }
                printf("max{%d,%d} = %d | ", K[i - 1][w], K[i - 1][w - item[i - 1][1]] + item[i - 1][0], K[i][w]);
            }
        }
        printf("\n");
    }

    // 결과 출력
	printf("\n< 결과 >\n");
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