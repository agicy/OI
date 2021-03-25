#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int p=1e9+7;
const int MAXSIZE=1e5+5;

char S[MAXSIZE];

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

int dp[MAXSIZE][2];

int main(void){
	reg int T=read();
	while(T--){
		scanf("%s",S+1);
		reg int n=strlen(S+1);
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(reg int i=1;i<=n;++i){
			if(S[i]=='1')
				dp[i][1]=add(dp[i][1],add(mul(3,dp[i-1][1]),dp[i-1][0]));
			else
				dp[i][1]=add(dp[i][1],mul(2,dp[i-1][1]));
			dp[i][0]=dp[i-1][0];
		}
		printf("%d\n",add(dp[n][0],dp[n][1]));
	}
	return 0;
}