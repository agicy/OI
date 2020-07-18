#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int p=998244353;
const int g=3;
const int invg=332748118;

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res; 
}

const int MAXSIZE=800000+5;

int n;
int G[MAXSIZE];

namespace Poly{
	int r[MAXSIZE];
	inline int Init(reg int len){
		reg int limit=1,l=0;
		while(limit<=len)
			limit<<=1,++l;
		for(reg int i=1;i<limit;++i)
			r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg int a[],reg int limit,reg int type){
		for(reg int i=0;i<limit;++i)
			if(i<r[i])
				swap(a[i],a[r[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=pow(type==1?g:invg,(p-1)/(i<<1),p);
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
					a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
				}
			}
		}
		if(type==-1){
			reg int inv=pow(limit,p-2,p);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	inline void Work(reg int deg,reg int f[],reg int res[]){
		if(deg==1){
			res[0]=pow(f[0],p-2,p);
			return;
		}
		Work((deg+1)>>1,f,res);
		reg int limit=Init(deg<<1);
		static int tmp[MAXN<<2];
		for(reg int i=0;i<deg;++i)
			tmp[i]=f[i];
		for(reg int i=deg;i<limit;++i)
			tmp[i]=0;
		NTT(tmp,limit,1),NTT(res,limit,1);
		for(reg int i=0;i<limit;++i)
			res[i]=1ll*(2ll-1ll*tmp[i]*res[i]%p+p)%p*res[i]%p;
		NTT(res,limit,-1);
		for(reg int i=deg;i<limit;++i)
			res[i]=0;
		return;
	}
	inline void inv(reg int res[],reg int f[],reg int n){
		Work(n,f,res);
		return;
	}
}

int f[MAXSIZE];

int main(void){
	n=read();
	for(reg int i=1;i<n;++i)
		G[i]=read();
	for(reg int i=1;i<n;++i)
		G[i]=(p-G[i])%p;
	G[0]=1;
	Poly::inv(f,G,n);
	for(reg int i=0;i<n;++i)
		printf("%d%c",f[i],i==n-1?'\n':' ');
	return 0;
}
