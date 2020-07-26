#include <cstdio>
#define abs(a) ((a) > 0 ? (a) : (-(a)))

double n, m;

int main(void)
{
	scanf("%lf%lf", &n, &m);
	printf("%.4f\n", abs(360.0 - abs(5.5 * m - 30 * n)) > 180 ? abs(360.0 - abs(360.0 - abs(5.5 * m - 30 * n))) : abs(360.0 - abs(5.5 * m - 30 * n)));
	return 0;
}