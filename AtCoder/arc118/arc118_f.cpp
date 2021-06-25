#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int mod=998244353;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
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

int n;
ll m;
int a[MAXN];
ll R[MAXN];
modInt fac[MAXN],invfac[MAXN];
modInt F[MAXN][MAXN];
modInt lef[MAXN],rig[MAXN];

inline modInt Lagrange(const modInt* val,const int& siz,modInt pos){
	if(pos.x<siz)
		return val[pos.x];
	else{
		lef[0]=pos;
		for(reg int i=1;i<siz;++i)
			lef[i]=lef[i-1]*(pos-i);
		rig[siz-1]=pos-(siz-1);
		for(reg int i=siz-2;i>=0;--i)
			rig[i]=rig[i+1]*(pos-i);
		modInt res=0;
		for(reg int i=0;i<siz;++i){
			modInt pod=1;
			if(i>0)
				pod*=lef[i-1]*invfac[i];
			if(i<siz-1)
				pod*=rig[i+1]*(((siz-1-i)&1)?-invfac[siz-1-i]:invfac[siz-1-i]);
			res+=val[i]*pod;
		}
		return res;
	}
}

int main(void){
	n=read(),m=readll();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	fac[0]=1;
	for(reg int i=1;i<=n+1;++i)
		fac[i]=fac[i-1]*i;
	invfac[n+1]=fpow(fac[n+1],mod-2);
	for(reg int i=n;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	R[n+1]=m,F[n+1][0]=1,F[n+1][1]=2;
	for(reg int i=n;i>=1;--i){
		R[i]=R[i+1]/a[i];
		modInt valr=Lagrange(F[i+1],n+2-i,modInt(R[i+1]%mod)-1);
		if(a[i]==1){
			static modInt tmp[MAXN];
			tmp[0]=F[i+1][0];
			for(reg int j=1,siz=n+2-i;j<siz;++j)
				tmp[j]=tmp[j-1]+F[i+1][j];
			F[i][0]=valr;
			modInt sum=valr+valr;
			for(reg int j=1,siz=n+3-i;j<siz;++j,sum+=valr)
				F[i][j]=sum-tmp[j-1];
		}
		else{
			static modInt f[MAXN];
			for(reg int j=0,siz=n+2-i;j<siz;++j)
				f[j]=valr-Lagrange(F[i+1],n+2-i,modInt(a[i]%mod)*(j+1)-2);
			F[i][0]=Lagrange(f,n+2-i,0);
			for(reg int j=1,siz=n+3-i;j<siz;++j)
				F[i][j]=F[i][j-1]+Lagrange(f,n+2-i,j);
		}
	}
	modInt ans=Lagrange(F[1],n+2,modInt(R[1]%mod)-1);
	printf("%d\n",ans.x);
	return 0;
}