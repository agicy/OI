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

const int MAXN=1.6e5+5;

namespace Poly{
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
	typedef vector<int> poly;
	poly rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=1;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(poly& a,reg int limit,reg int flag){
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
}

using namespace Poly;

int n,m;
int f[MAXN];
int fac[MAXN<<1],invfac[MAXN<<1],inv[MAXN<<1];
int mfac[MAXN<<1],minvfac[MAXN<<1],minv[MAXN<<1];

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<=n;++i)
		f[i]=read();
	fac[0]=mfac[0]=1;
	for(reg int i=1;i<=2*n+1;++i){
		fac[i]=1ll*fac[i-1]*i%p;
		mfac[i]=1ll*mfac[i-1]*(m+i-n-1)%p;
	}
	invfac[2*n+1]=fpow(fac[2*n+1],p-2);
	minvfac[2*n+1]=fpow(mfac[2*n+1],p-2);
	for(reg int i=2*n;i>=0;--i){
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		minvfac[i]=1ll*minvfac[i+1]*(m+i-n)%p;
	}
	for(reg int i=2*n+1;i>=1;--i){
		inv[i]=1ll*invfac[i]*fac[i-1]%p;
		minv[i]=1ll*minvfac[i]*mfac[i-1]%p;
	}
	inv[0]=minv[0]=1;
	poly a,b;
	reg int limit=getRev(3*n+1);
	a.resize(limit),b.resize(limit);
	for(reg int i=0;i<=n;++i){
		a[i]=1ll*f[i]*invfac[i]%p*invfac[n-i]%p;
		if((n-i)&1)
			a[i]=p-a[i];
	}
	for(reg int i=0;i<=2*n;++i)
		b[i]=minv[i+1];
	NTT(a,limit,1),NTT(b,limit,1);
	for(reg int i=0;i<limit;++i)
		a[i]=1ll*a[i]*b[i]%p;
	NTT(a,limit,-1);
	for(reg int i=n;i<=2*n;++i)
		printf("%lld%c",1ll*mfac[i+1]*minvfac[i-n]%p*a[i]%p,i==2*n?'\n':' ');
	return 0;
}