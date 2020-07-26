#include <cmath>
#include <cstdio>
#define eps 1e-6

long long n;

int main(void)
{
	register long long temp = 0;
	register double sqr;
	scanf("%lld", &n);
	if (n == 1)
		return puts("None"), 0;
	puts("1");
	temp = n + 1;
	while(true)
	{
		sqr = sqrt(temp);
		if(sqr>=n)
			break;
		if (sqr==(int)sqr)
			printf("%d\n", (int)sqr);
		temp += n ;
	}
	return 0;
}