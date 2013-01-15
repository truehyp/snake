/*蟑螂漫步问题
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX 50000

int ibug, jbug;
int imove[8] = {-1, 0, 1, 1, 1, 0, -1, -1}, jmove[8] = {1, 1, 1, 0, -1, -1, -1, 0};
int n, m;

int main (void)
{
	int k;
	int sum ;
	int i, j;
	int flag = 0;

	printf ("Input the n and m:");
	if (scanf ("%d%d", &n, &m) != 2)
	{
		printf ("Can't scanf\n");
		exit(1);
	}

	if (n <= 2 || n > 40 || m < 2 || m > 20)
	{
		printf ("Input the n and m that 2 < n <=40,2 <= m <= 20\n");
	        exit(1);	
	}

	int floor[n][m];	//floor array element are all zero
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			floor[i][j] = 0;
	
	printf ("Input the bug coordinate:");
	if (scanf ("%d%d", &ibug, &jbug) != 2)
	{
		printf ("Can't scanf ibug, jbug\n");
		exit(1);
	}

	if (ibug < 0 ||ibug >= n || jbug < 0 ||jbug >= m)
	{
		printf ("The bug corrdinate is out of the floor array\n");
		exit(1);
	}
	
	floor[ibug][jbug] ++;
	
	for (sum = 0 ; sum <= MAX && !flag; sum++) 
	{
		flag = 1;
		while (1) //bug moving
		{
			k = rand() % 8;
			if (ibug + imove[k] >= 0 && ibug + imove[k] < n && jbug + jmove[k] >= 0 && jbug + jmove[k] < m)
			{
				ibug = ibug + imove[k];
				jbug = jbug + jmove[k];
				break;
			}
		}
		floor[ibug][jbug] ++;
		for (i = 0; i < n; i++)	//check floor array
		{
			for (j = 0; j < m; j++)
			{
				if (floor[i][j] == 0)
				{
					flag = 0;
					break;
				}
			}
			if (!flag)
				break;
		}
	}

	printf ("the bug moved %d step", sum);
	printf ("the floor is like that\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf ("%8d", floor[i][j]);
		printf ("\n");
	}

	return 0;
}
