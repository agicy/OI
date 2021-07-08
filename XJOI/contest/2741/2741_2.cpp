#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e7+5;
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

int n,w1,w2,s;
int fac[MAXN<<1],invfac[MAXN<<1];

inline void init(reg int n){
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

inline int getPow(reg int a,reg int b){
	return 1ll*fpow(w1,a)*fpow(w2,b)%mod;
}

inline int getVal(reg int cnt){
	if(n>=cnt)
		return 1ll*binom(cnt,n-cnt)*getPow(2*cnt-n,n-cnt)%mod;
	else
		return 0;
}

inline int getCnt(reg int bl,reg int wh){
	return binom(bl+wh-1,bl-wh);
}

int main(void){
	scanf("%d%d%d%d",&n,&w1,&w2,&s);
	init(n<<1);
	reg int ans=0;
	for(reg int i=1;i<=s;++i)
		ans=add(ans,1ll*getVal(s+i)*getCnt(s,i)%mod);
	printf("%d\n",ans);
	return 0;
}