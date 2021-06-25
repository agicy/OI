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

const int MAXN=2e3+5;
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
int fa[MAXN];
int siz[MAXN];
modInt f[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i)
		fa[i]=read();
	for(reg int i=1;i<=n;++i)
		f[i][0]=1;
	for(reg int u=n;u>=1;--u){
		++siz[u];
		for(reg int i=siz[u];i>=1;--i)
			f[u][i]+=f[u][i-1]*(siz[u]-i);
		if(fa[u]){
			reg int father=fa[u];
			static modInt tmp[MAXN];
			fill(tmp,tmp+siz[u]+siz[father]+1,0);
			for(reg int i=0;i<=siz[u];++i)
				for(reg int j=0;j<=siz[father];++j)
					tmp[i+j]+=f[u][i]*f[father][j];
			for(reg int i=0;i<=siz[u]+siz[father];++i)
				f[father][i]=tmp[i];
			siz[father]+=siz[u];
		}
	}
	modInt ans=0,fac=1;
	for(reg int i=n-1;i>=0;--i){
		fac*=n-i;
		if(i&1)
			ans-=f[1][i]*fac;
		else
			ans+=f[1][i]*fac;
	}
	printf("%d\n",ans.x);
	return 0;
}