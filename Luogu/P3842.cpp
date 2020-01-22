#include <cstdio>
#define abs(a) ((a) < 0 ? (-(a)) : (a))
#define min(a, b) ((a) < (b) ? (a) : (b))

int n;
int L[20001], R[20001];
int dp[2][20002];

int main(void)
{
    register int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &L[i], &R[i]);
    dp[0][1] = (R[1] - 1) + (R[1] - L[1]);
    dp[1][1] = R[1] - 1;
    for (i = 2; i <= n; ++i)
    {
        dp[0][i] = min(dp[0][i - 1] + 1 + abs(L[i - 1] - R[i]) + (R[i] - L[i]), dp[1][i - 1] + 1 + abs(R[i - 1] - R[i]) + (R[i] - L[i]));
        dp[1][i] = min(dp[0][i - 1] + 1 + abs(L[i - 1] - L[i]) + (R[i] - L[i]), dp[1][i - 1] + 1 + abs(R[i - 1] - L[i]) + (R[i] - L[i]));
    }
    printf("%d\n", min(dp[0][n] + (n - L[n]), dp[1][n] + (n - R[n])));
    return 0;
}