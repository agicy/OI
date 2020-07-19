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

const int p=998244353;
const int g=3;
const int invg=332748118;

inline int readmod(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=(10ll*res+ch-'0')%p,ch=getchar();
	return res;
}

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

const int MAXN=100000+5;
const int MAXSIZE=800000+5;

namespace Poly{
	int inv_[MAXSIZE];
	inline void Init(void){
		inv_[1]=1;
		for(reg int i=2;i<MAXSIZE;++i)
        	inv_[i]=1ll*(p-p/i)*inv_[p%i]%p;
	}
	int r[MAXSIZE];
	inline int Init(const int len){
		reg int limit=1,l=0;
		while(limit<len)
			limit<<=1,++l;
		for(reg int i=1;i<limit;++i)
			r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void diff(reg int res[],const int f[],const int n){
		for(reg int i=0;i<n-1;++i)
			res[i]=1ll*f[i+1]*(i+1)%p;
		return;
	}
	inline void sum(reg int res[],const int f[],const int n){
		for(reg int i=n;i>=1;--i)
			res[i]=1ll*f[i-1]*inv_[i]%p;
		res[0]=0;
		return;
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
	inline void mul(reg int res[],const int a[],const int la,const int b[],const int lb){
		static int A[MAXSIZE],B[MAXSIZE];
		reg int limit=Init(la+lb);
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
	inline void inv(reg int res[],const int f[],reg int n){
		if(n==1){
			res[0]=pow(f[0],p-2,p);
			return;
		}
		inv(res,f,(n+1)>>1);
		reg int limit=Init(n<<1);
		static int tmp[MAXSIZE];
		for(reg int i=0;i<n;++i)
			tmp[i]=f[i];
		for(reg int i=n;i<limit;++i)
			tmp[i]=0;
		NTT(tmp,limit,1),NTT(res,limit,1);
		for(reg int i=0;i<limit;++i)
			res[i]=1ll*(2ll-1ll*tmp[i]*res[i]%p+p)%p*res[i]%p;
		NTT(res,limit,-1);
		for(reg int i=n;i<limit;++i)
			res[i]=0;
		return;
	}
	inline void ln(reg int res[],const int f[],reg int n){
		static int df[MAXSIZE];
		static int invf[MAXSIZE];
		memset(invf,0,sizeof(invf));
		diff(df,f,n);
		inv(invf,f,n);
		mul(df,df,n-1,invf,n);
		sum(res,df,n);
		res[0]=0;
		return;
	}
	inline void exp(reg int res[],const int f[],reg int n){
		if(n==1){
			res[0]=1;
			return;
		}
		exp(res,f,(n+1)>>1);
		static int Ln[MAXSIZE];
		ln(Ln,res,n);
		reg int limit=Init(n<<1);
		for(reg int i=0;i<n;++i)
			Ln[i]=f[i]>=Ln[i]?f[i]-Ln[i]:f[i]-Ln[i]+p;
		for(reg int i=n;i<limit;++i)
			Ln[i]=res[i]=0;
		++Ln[0];
		NTT(Ln,limit,1),NTT(res,limit,1);
		for(reg int i=0;i<limit;++i)
			res[i]=1ll*res[i]*Ln[i]%p;
		NTT(res,limit,-1);
		for(reg int i=n;i<limit;++i)
			res[i]=0;
		return;
	}
}

int n,k;
int a[MAXSIZE];
int tmp[MAXSIZE];
int ans[MAXSIZE];

int main(void){
	Poly::Init();
	n=read(),k=readmod();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	Poly::ln(tmp,a,n);
	for(reg int i=0;i<n;++i)
		tmp[i]=1ll*tmp[i]*k%p;
	Poly::exp(ans,tmp,n);
	for(reg int i=0;i<n;++i)
		printf("%d%c",ans[i],i==n-1?'\n':' ');
	return 0;
}
