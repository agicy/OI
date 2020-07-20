#include <cstdio>
#include <cstring>

char str[1002];
int n;

int main(void)
{
	register int i;
	scanf("%d%s", &n, str + 1);
	str[0] = str[n + 1] = '0';
	for (i = 1; i <= n; ++i)
		if (str[i] == '0' && !(str[i - 1] == '1' || str[i + 1] == '1'))
			return puts("No"), 0;
		else if (str[i] == '1' && (str[i - 1] == '1' || str[i + 1] == '1'))
			return puts("No"), 0;
		else
			continue;
	puts("Yes");
	return 0;
}