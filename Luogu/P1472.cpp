#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=200+5;
const int MAXK=100+5;
const int p=9901;

int n,k;
int dp[MAXN][MAXK];

int main(void){
	scanf("%d%d",&n,&k);
	for(reg int i=1;i<=k;++i)
		dp[1][i]=1;
	for(reg int d=1;d<=k;++d)
		for(reg int i=3;i<=n;i+=2)
			for(reg int j=1;j<i;j+=2)
				dp[i][d]=(dp[i][d]+dp[j][d-1]*dp[i-j-1][d-1]%p)%p;
	printf("%d\n",(dp[n][k]-dp[n][k-1]+p)%p);
	return 0;
}