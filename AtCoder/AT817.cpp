#include <cstdio>

char str[7] = "123456";
int a;

void swap(char&, char&);

int main(void)
{
    register int i, now = 0;
    scanf("%d", &a);
    a %= 30;
    for (i = 0; i < a; ++i) {
        swap(str[now], str[now + 1]);
        if (++now == 5)
            now = 0;
    }
    puts(str);
    return 0;
}

void swap(char& a, char& b)
{
    a ^= b, b = a ^ b, a ^= b;
    return;
}