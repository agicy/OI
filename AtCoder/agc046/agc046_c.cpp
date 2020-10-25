#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353

const int MAXN=300+5;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=MOD?sum-MOD:sum;
}

char S[MAXN];
int a[MAXN],K;
int dp[2][MAXN][MAXN];

int main(void){
	scanf("%s%d",S,&K);
	reg int n=strlen(S);
	int sum=0;
	reg int tot=0,cnt=0;
	for(reg int i=0;i<=n;++i)
		if(S[i]=='1')
			++cnt,++sum;
		else{
			a[++tot]=cnt;
			cnt=0;
		}
	reg int t=0;
	dp[0][0][0]=1;
	for(reg int i=tot;i>=1;--i){
		for(reg int j=0;j<=t;++j)
			for(reg int k=0;k<=t;++k){
				dp[1][j][k]=dp[0][j][k];
				dp[0][j][k]=0;
			}
		for(reg int j=0;j<=t;++j){
			dp[0][j][t]=dp[1][j][t];
			for(reg int k=t-1;k>=0;--k)
				dp[0][j][k]=add(dp[0][j][k+1],dp[1][j][k]);
		}
		for(reg int j=0;j<=t;++j)
			for(reg int k=0;k<=t;++k)
				for(reg int l=1;l<=a[i];++l)
					dp[0][j+l][k+l]=add(dp[0][j+l][k+l],dp[1][j][k]);
		t+=a[i];
	}
	reg int ans=0,Max=min(K,sum);
	for(reg int i=0;i<=Max;++i)
		ans=add(ans,dp[0][i][0]);
	printf("%d\n",ans);
	return 0;
}