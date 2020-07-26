#include <algorithm>
#include <cmath>
#include <cstdio>
using std::swap;

struct Complex
{
	double x, y;
	Complex(void)
	{
		x = y = 0;
		return;
	}
	Complex(double _x, double _y)
	{
		x = _x, y = _y;
		return;
	}
	Complex operator+(Complex op)
	{
		return Complex(this->x + op.x, this->y + op.y);
	}
	Complex operator-(Complex op)
	{

		return Complex(this->x - op.x, this->y - op.y);
	}
	Complex operator*(Complex op)
	{
		return Complex(
			this->x * op.x - this->y * op.y,
			this->x * op.y + this->y * op.x);
	}
};

char str1[60001], str2[60001];
int n, limit = 1, l, r[131073], ans[131073];
Complex a[131073], b[131073];

void FFT(Complex a[], int f);

int main(void)
{
	register bool flag = false;
	register int i;
	scanf("%d%s%s", &n, str1, str2);
	for (i = 0; i < n; ++i)
	{
		a[i].x = str1[n - i - 1] - '0';
		b[i].x = str2[n - i - 1] - '0';
	}
	while (limit <= (n << 1))
		limit <<= 1, ++l;
	for (i = 0; i < limit; ++i)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	FFT(a, 1);
	FFT(b, 1);
	for (i = 0; i <= limit; ++i)
		a[i] = a[i] * b[i];
	FFT(a, -1);
	for (i = 0; i <= (n << 1); ++i)
		ans[i] = (int)(a[i].x / limit + 0.5);
	for (i = 0; i <= (n << 1); ++i)
		if (ans[i] >= 10)
		{
			ans[i + 1] += ans[i] / 10;
			ans[i] %= 10;
		}
	for (i = (n << 1); i >= 0; --i)
		if (flag || (!flag && ans[i]))
		{
			flag = true;
			putchar(ans[i] + '0');
		}
	putchar('\n');
	return 0;
}

void FFT(Complex a[], int f)
{
#define M_PI 3.14159265358979323846
	register int i, j, k;
	Complex w, e, x, y;
	for (i = 0; i < limit; ++i)
		if (i < r[i])
			swap(a[i], a[r[i]]);
	for (i = 1; i < limit; i <<= 1)
	{
		w = Complex(cos(M_PI / i), f * sin(M_PI / i));
		for (j = 0; j < limit; j += i << 1)
		{
			e = Complex(1, 0);
			for (k = 0; k < i; ++k, e = e * w)
			{
				x = a[j + k], y = a[j + k + i] * e;
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
	return;
#undef M_PI
}
