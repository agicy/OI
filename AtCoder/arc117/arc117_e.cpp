#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=30+5;

int n,K;
ll f[MAXN<<1][MAXN*MAXN][MAXN];
ll binom[MAXN][MAXN];

int main(void){
	scanf("%d%d",&n,&K);
	binom[0][0]=1;
	for(reg int i=1;i<=n;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=binom[i-1][j-1]+binom[i-1][j];
	}
	f[0][0][0]=1;
	for(reg int i=0;i<=n*2+1;++i)
		for(reg int j=0;j<=n*n;++j)
			for(reg int k=0;k<=n+1;++k){
				if(!f[i][j][k])
					continue;
				for(reg int l=k+1;l<=min(n+1,2*n-i+1);++l)
					f[i+l][j+l*(l-1)/2][l-k]+=f[i][j][k]*binom[l-1][k];
			}
	reg ll res=0;
	for(reg int i=0;i<=2*n+1;++i)
		for(reg int j=0;j<=n*n;++j)
			for(reg int k=0;k<=n+1;++k){
				if(!f[i][j][k])
					continue;
				if(!k||j>K)
					continue;
				res+=f[i][j][k]*f[2*n-i+1][K-j][k-1];
			}
	printf("%lld\n",res);
	return 0;
}