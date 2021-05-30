#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
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

const int MAXN=16;
const int MAXM=16;

int n,m;
int a[MAXN];
modInt f[MAXN+1][1<<MAXN];
modInt fac[1<<MAXN],invfac[1<<MAXN];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<n;++i)
		fac[i]=fac[i-1]*i;
	invfac[n-1]=fpow(fac[n-1],mod-2);
	for(reg int i=n-2;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	return;
}

inline modInt binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return fac[n]*invfac[m]*invfac[n-m];
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int lg(reg int x){
	switch(x){
		case 1<<0:return 0;
		case 1<<1:return 1;
		case 1<<2:return 2;
		case 1<<3:return 3;
		case 1<<4:return 4;
		case 1<<5:return 5;
		case 1<<6:return 6;
		case 1<<7:return 7;
		case 1<<8:return 8;
		case 1<<9:return 9;
		case 1<<10:return 10;
		case 1<<11:return 11;
		case 1<<12:return 12;
		case 1<<13:return 13;
		case 1<<14:return 14;
		case 1<<15:return 15;
	}
	return -1;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<m;++i)
		a[i]=read();
	Init(1<<n);
	f[m][0]=1;
	reg int U=(1<<n)-1;
	for(reg int i=m-1;i>=0;--i)
		for(reg int S=0;S<=U;++S){
			f[i][S]+=f[i+1][S];
			for(reg int T=(~S)&U;T;T^=lowbit(T))
				f[i][S|lowbit(T)]+=f[i+1][S]*binom((1<<n)-S-a[i],lowbit(T)-1)*fac[lowbit(T)];
		}
	modInt ans=0;
	for(reg int S=0;S<=U;++S)
		if(__builtin_parity(S))
			ans-=f[0][S]*fac[U^S];
		else
			ans+=f[0][S]*fac[U^S];
	printf("%d\n",(ans*(1<<n)).x);
	return 0;
}