#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=998244353;
const int MAXN=2e6+5;

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

int n,m;
int fac[MAXN],invfac[MAXN];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	return;
}

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

int main(void){
	scanf("%d%d",&n,&m);
	if(n<m) swap(n,m);
	Init(n+m);
	reg int sum=0;
	for(reg int i=1;i<=m;++i)
		sum=add(sum,1ll*binom(n+m-(i<<1),m-i)*binom(i<<1,i)%mod);
	printf("%d\n",add(1ll*sum*fpow(2,mod-2)%mod*fpow(binom(n+m,n),mod-2)%mod,n));
	return 0;
}