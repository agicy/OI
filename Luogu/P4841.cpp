#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
static char buf[100000],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int p=1004535809;
const int g=3;
const int invg=334845270;

const int MAXN=1000000+5;

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

inline int inv(reg int x,reg int mod){
	return pow(x,mod-2,mod);
}

namespace Poly{
	int r[MAXN];
	inline int Init(reg int S){
		reg int limit=1,l=0;
		while(limit<=S)
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
	inline void Inv(reg int res[],reg int a[],reg int deg){
		if(deg==1){
			res[0]=inv(a[0],p);
			return;
		}
		Inv(res,a,(deg+1)>>1);
		reg int limit=Init(deg<<1);
		static int c[MAXN<<2];
		for(reg int i=0;i<deg;++i)
			c[i]=a[i];
		for(reg int i=deg;i<limit;++i)
			c[i]=0;
		NTT(c,limit,1),NTT(res,limit,1);
		for(reg int i=0;i<limit;++i)
			res[i]=1ll*(2ll-1ll*c[i]*res[i]%p+p)%p*res[i]%p;
		NTT(res,limit,-1);
		for(reg int i=deg;i<limit;++i)
			res[i]=0;
		return;
	}
	inline void Mul(reg int res[],reg int a[],reg int la,reg int b[],reg int lb){
		reg int limit=Init(la+lb);
		static int A[MAXN],B[MAXN];
		for(reg int i=0;i<la;++i)
			A[i]=a[i];
		for(reg int i=la;i<limit;++i)
			A[i]=0;
		for(reg int i=0;i<lb;++i)
			B[i]=b[i];
		for(reg int i=lb;i<limit;++i)
			B[i]=0;
		NTT(A,limit,1),NTT(B,limit,1);
		for(reg int i=0;i<limit;++i)
			res[i]=1ll*A[i]*B[i]%p;
		NTT(res,limit,-1);
		for(reg int i=la+lb;i<limit;++i)
			res[i]=0;
		return;
	}
}

int n;
int fac[MAXN],finv[MAXN];
int res[MAXN],G[MAXN],Gp[MAXN],H[MAXN];

int main(void){
	n=read();
	if(n==0){
		puts("0");
		return 0;
	}
	fac[0]=1,finv[1]=1;
	for(reg int i=2;i<=n;++i)
		finv[i]=1ll*(p-p/i)*finv[p%i]%p;
	finv[0]=1;
	for(reg int i=1;i<=n;++i){
		fac[i]=1ll*fac[i-1]*i%p;
		finv[i]=1ll*finv[i-1]*finv[i]%p;
	}
	++n;
	G[0]=1;
	for(reg int i=1;i<n;++i){
		reg int tmp=pow(2,((1ll*(i)*(i-1ll))>>1ll)%(p-1),p);
		G[i]=1ll*tmp*finv[i]%p;
		H[i]=1ll*tmp*finv[i-1]%p;
	}
	Poly::Inv(Gp,G,n);
	Poly::Mul(res,Gp,n,H,n);
	printf("%lld\n",1ll*res[n-1]*fac[n-2]%p);
	return 0;
}