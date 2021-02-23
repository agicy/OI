#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXA=1e5+5;
const int MAXB=1e5+5;
const int inf=0x3f3f3f3f;
const int MAXSIZE=16384;
const int p=998244353;
const int g=3;
const int invg=332748118;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

namespace Poly{
	int rev[MAXSIZE];
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg int a[],reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=fpow(flag==1?g:invg,(p-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[i+j+k]%p;
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
			}
		}
		if(flag==-1){
			reg int inv=fpow(limit,p-2);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	inline void mul(reg int a[],reg int lena,reg int b[],reg int lenb,reg int res[]){
		reg int s=lena+lenb-1;
		reg int limit=getRev(s);
		for(reg int i=lena;i<limit;++i)
			a[i]=0;
		for(reg int i=lenb;i<limit;++i)
			b[i]=0;
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			res[i]=1ll*a[i]*b[i]%p;
		NTT(res,limit,-1);
		return;
	}
}

int F[MAXSIZE],G[MAXSIZE],tmp[MAXSIZE];
int fac[MAXA+MAXB],invfac[MAXA+MAXB];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	return;
}

int main(void){
	Init(2e5);
	reg int n=read();
	reg int lF=1;
	F[0]=1;
	while(n--){
		reg int a=read(),b=read();
		reg int Maxj=a-b+lF,Maxk=lF;
		reg int ptr=inf;
		reg int lG=0;
		for(reg int i=-Maxk;i<Maxj;++i)
			if(0<=a-i&&0<=b+i){
				if(ptr==inf)
					ptr=i;
				G[lG++]=1ll*invfac[a-i]*invfac[b+i]%p;
			}
		Poly::mul(F,lF,G,lG,tmp);
		reg int tot=0;
		for(reg int i=0,siz=lF+lG-1;i<siz;++i){
			if(0<=ptr&&ptr<Maxj)
				F[tot++]=1ll*tmp[i]*fac[a+b]%p;
			++ptr;
		}
		lF=tot;
	}
	reg int ans=0;
	for(reg int i=0;i<lF;++i)
		ans=add(ans,F[i]);
	printf("%d\n",ans);
	return 0;
}