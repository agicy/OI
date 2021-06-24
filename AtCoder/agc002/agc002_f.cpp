#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

const int MAXN=2e3+5;
const int MAXK=2e3+5;

int n,k;
modInt fac[MAXN*MAXK],invfac[MAXN*MAXK];

inline modInt binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return fac[n]*invfac[m]*invfac[n-m];
}

modInt f[MAXN][MAXN];

int main(void){
	scanf("%d%d",&n,&k);
	if(k==1)
		puts("1");
	else{
		f[0][0]=1;
		fac[0]=1;
		for(reg int i=1;i<=n*k;++i)
			fac[i]=fac[i-1]*i;
		invfac[n*k]=fpow(fac[n*k],mod-2);
		for(reg int i=n*k-1;i>=0;--i)
			invfac[i]=invfac[i+1]*(i+1);
		f[0][0]=1;
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<=i;++j)
				f[i][j]=f[i-1][j]+f[i][j-1]*binom(n*k-(j-1)*(k-1)-i-1,k-2)*(n-j+1);
		printf("%d\n",f[n][n].x);
	}
	return 0;
}