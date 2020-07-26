#include <cstdio>

int a[2][3];

int main(void)
{
	register int i, j;
	for (i = 0; i < 2; ++i)
		for (j = 0; j < 3; ++j)
			scanf("%d", &a[i][j]);
	for (i = 0; i < 3; ++i)
		if (a[0][i] == a[1][i])
			return puts("YES"), 0;
	return puts("NO"), 0;
}