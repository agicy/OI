#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e3+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,k,p;
int limit,dp[MAXN*MAXN],sum[MAXN*MAXN];

int main(void){
	scanf("%d%d%d",&n,&k,&p);
	reg int limit=1;
	for(reg int i=k+1;i<=n;++i)
		limit+=min(i-k+1,k);
	if(p>limit)
		puts("0");
	else{
		dp[1]=1;
		for(reg int i=1;i<=k;++i)
			dp[1]=1ll*dp[1]*i%mod;
		limit=1;
		for(reg int i=k+1;i<=n;++i){
			reg int Maxdelta=min(i-k+1,k);
			limit+=Maxdelta;
			for(reg int j=1;j<=limit&&j<=p;++j)
				sum[j]=add(sum[j-1],dp[j]);
			for(reg int j=min(p,limit);j;--j){
				dp[j]=2ll*sub(sum[j-1],sum[j>Maxdelta?j-Maxdelta:0])%mod;
				if(j>=Maxdelta)
					dp[j]=add(dp[j],1ll*(i-2*(Maxdelta-1))*dp[j-Maxdelta]%mod);
			}
		}
		printf("%d\n",dp[p]);
	}
	return 0;
}