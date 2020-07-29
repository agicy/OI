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

const int MAXN=1e5+5;

namespace Poly{
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
	inline int Init(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
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
	inline void mul(reg int res[],const int a[],reg int la,const int b[],reg int lb){
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
			A[i]=1ll*A[i]*B[i]%p;
		NTT(A,limit,-1);
		for(reg int i=0;i<la+lb;++i)
			res[i]=A[i];
		return;
	}
}

int n;
int a[MAXN];
int p[MAXN];

inline void

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	for(reg int i=0;i<n;++i){
		static int x,y;
		x=read(),y=read();
		p[i]=1ll*x*pow(y,Poly::p-2,Poly::p)%Poly::p;
	}
	build(1,1,n);
	
	for(reg int i=0;i<n;++i){
		
	}
	return 0;
}
