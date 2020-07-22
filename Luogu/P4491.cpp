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

const int p=1004535809;
const int g=3;
const int invg=334845270;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
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

const int MAXN=10000000+5;
const int MAXM=100000+5;
const int MAXC=MAXM;

int n,m,s;
int w[MAXM];

const int MAXSIZE=800000+5;

namespace Poly{
	int r[MAXSIZE];
	inline int Init(const int len){
		reg int limit=1,l=0;
		while(limit<len)
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
}

int fac[MAXN],invfac[MAXN];

inline void Init(reg int n){
	fac[0]=fac[1]=invfac[0]=invfac[1]=1;
	for(reg int i=2;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=pow(fac[n],p-2,p);
	for(reg int i=n-1;i>=2;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1ll)%p;
	return;
}

int f[MAXC];
int a[MAXSIZE],b[MAXSIZE];
int ans[MAXC];

inline int binom(reg int n,reg int m){
	return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

int main(void){
	n=read(),m=read(),s=read();
	for(reg int i=0;i<=m;++i)
		w[i]=read();
	Init(max(n,m));
	reg int C=min(n/s,m);
	for(reg int i=0;i<=C;++i)
		f[i]=1ll*binom(m,i)*binom(n,i*s)%p*fac[i*s]%p*pow(invfac[s],i,p)%p*pow(m-i,n-i*s,p)%p;
	for(reg int i=0;i<=C;++i){
		a[i]=(i&1)?((p-invfac[i])%p):(invfac[i]);
		b[i]=1ll*f[i]*fac[i]%p;
	}
	reverse(b,b+C+1);
	reg int limit=Poly::Init(C*2+2);
	Poly::NTT(a,limit,1),Poly::NTT(b,limit,1);
	for(reg int i=0;i<limit;++i)
		a[i]=1ll*a[i]*b[i]%p;
	Poly::NTT(a,limit,-1);
	reverse(a,a+C+1);
	reg int ans=0;
	for(reg int i=0;i<=C;++i)
		ans=add(ans,1ll*a[i]*w[i]%p*invfac[i]%p);
	printf("%d\n",ans);
	return 0;
}
