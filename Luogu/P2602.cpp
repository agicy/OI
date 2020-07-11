#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=12+5;

ll l,r;
ll ans[10][2];
ll dp[MAXN][10][10];

inline ll Quickpow(reg ll x,reg ll exp){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x;
		exp>>=1;
	}
	return res;
}

inline void Solve(reg ll n,int opt){
	reg int cnt=0;
	static int a[MAXN];
	while(n){
		a[++cnt]=n%10;
		n/=10;
	}
	memset(dp,0,sizeof(dp));
	for(reg int i=0;i<=9;++i)
		dp[1][i][i]=1;
	for(reg int i=2;i<=cnt;++i)
		for(reg int j=0;j<=9;++j){
			for(reg int k=0;k<=9;++k)
				for(reg int l=0;l<=9;++l)
					dp[i][j][l]+=dp[i-1][k][l];
			dp[i][j][j]+=Quickpow(10,i-1);
		}
	for(reg int i=1;i<cnt;++i)
		for(reg int j=1;j<=9;++j)
			for(reg int k=0;k<=9;++k)
				ans[k][opt]+=dp[i][j][k];
	for(reg int i=1;i<a[cnt];++i)
		for(reg int j=0;j<=9;++j)
			ans[j][opt]+=dp[cnt][i][j];
	for(reg int i=cnt-1;i>=1;--i){
		for(reg int j=0;j<a[i];++j)
			for(reg int k=0;k<=9;++k)
				ans[k][opt]+=dp[i][j][k];
		for(reg int j=cnt;j>i;--j)
			ans[a[j]][opt]+=a[i]*Quickpow(10,i-1);
	}
	return;
}

int main(void){
	scanf("%lld%lld",&l,&r);
	Solve(l,0),Solve(r+1,1);
	for(reg int i=0;i<=9;++i)
		printf("%lld%c",ans[i][1]-ans[i][0],i==9?'\n':' ');
	return 0;
}
