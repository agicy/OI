#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

const int MAXSIZE=64;
const ll inv2=500000004;

ll n,m,k;
ll dp[MAXSIZE][2][2];
ll a[MAXSIZE],b[MAXSIZE];

int main(void){
	int T;
	scanf("%d%lld",&T,&k);
	while(T--){
		scanf("%lld%lld",&n,&m);
		m=min(n,m);
		reg ll ans=(m%MOD*((m+1)%MOD)%MOD*inv2%MOD+(n-m+1)%MOD*((m+1)%MOD)%MOD)%MOD;
		reg int cnta=0,cntb=0;
		while(n){
			a[++cnta]=n%k,b[++cntb]=m%k;
			n/=k,m/=k;
		}
		memset(dp,0,sizeof(dp));
		dp[cnta+1][1][1]=1;
		for(reg int i=cnta;i;--i)
			for(reg int j=0;j<2;++j)
				for(reg int l=0;l<2;++l){
					if(!dp[i+1][j][l])
						continue;
					reg int Maxx=j?a[i]:k-1,Maxy=l?b[i]:k-1;
					for(reg int x=0;x<=Maxx;++x)
						for(reg int y=0;y<=Maxy&&y<=x;++y)
							dp[i][j&&(x==Maxx)][l&&(y==Maxy)]=(dp[i][j&&(x==Maxx)][l&&(y==Maxy)]+dp[i+1][j][l])%MOD;
				}
		for(reg int i=0;i<2;++i)
			for(reg int j=0;j<2;++j)
				ans=(ans-dp[1][i][j]+MOD)%MOD;
		printf("%lld\n",ans%MOD);
	}
	return 0;
}