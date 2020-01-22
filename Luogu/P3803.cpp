#include <algorithm>
#include <cmath>
#include <cstdio>
using std::swap;

#define M_PI 3.14159265358979323846

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
static char buf[100000], *p1 = buf, *p2 = buf;

inline long long read(void)
{
    register bool f = false;
    register char ch = getchar();
    register long long sum = 0;
    while (!(ch >= '0' && ch <= '9'))
        ch = getchar(),
        f = (ch == '-') ? (!f) : (f);
    while (ch >= '0' && ch <= '9')
        sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
}

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

int n, m, limit = 1, l, r[10000001];
Complex a[10000001], b[10000001];

void FFT(Complex a[], int f);

int main(void)
{
    register int i;
    n = read(), m = read();
    for (i = 0; i <= n; ++i)
        a[i].x = read();
    for (i = 0; i <= m; ++i)
        b[i].x = read();
    while (limit <= n + m)
        limit <<= 1, ++l;
    for (i = 0; i < limit; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    FFT(a, 1);
    FFT(b, 1);
    for (i = 0; i <= limit; ++i)
        a[i] = a[i] * b[i];
    FFT(a, -1);
    for (i = 0; i <= n + m; ++i)
        printf("%d ", (int)(a[i].x / limit + 0.5));
    putchar('\n');
    return 0;
}

void FFT(Complex a[], int f)
{
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
}
