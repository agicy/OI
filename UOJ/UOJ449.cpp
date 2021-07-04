#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=50+5;
const int MAXK=1e3+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,k;
int fac[MAXN*MAXK],invfac[MAXN*MAXK],inv[MAXN*MAXK];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

int f[MAXN*MAXK][MAXN],g[MAXN*MAXK][MAXN];

int main(void){
	scanf("%d%d",&n,&k);
	fac[0]=1;
	for(reg int i=1;i<=n*k;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n*k]=fpow(fac[n*k],mod-2);
	for(reg int i=n*k-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	for(reg int i=1;i<=n*k;++i)
		inv[i]=1ll*invfac[i]*fac[i-1]%mod;
	f[0][0]=0,g[0][0]=1;
	for(reg int i=0;i<n*k;++i)
		for(reg int j=0;j*k<=i;++j){
			reg int tmp1=add(1ll*inv[n-j]*f[i][j]%mod,1ll*inv[n-j]*(1ll*n*inv[n-j]%mod)%mod*g[i][j]%mod),tmp2=1ll*inv[n-j]*g[i][j]%mod;
			if(j*k<=(i+1))
				f[i+1][j]=add(f[i+1][j],tmp1),g[i+1][j]=add(g[i+1][j],tmp2);
			if((j+1)*k<=(i+1))
				f[i+1][j+1]=add(f[i+1][j+1],1ll*binom(i-j*k,k-1)*tmp1%mod),g[i+1][j+1]=add(g[i+1][j+1],1ll*binom(i-j*k,k-1)*tmp2%mod);
		}
	reg int ans=1ll*fac[n]*f[n*k][n]%mod;
	printf("%d\n",ans);
	return 0;
}