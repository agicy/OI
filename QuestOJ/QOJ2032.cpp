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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

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
	vector<int> rev;
	int las;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		if(limit==las)
			return limit;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return las=limit;
	}
	typedef vector<int> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
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
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*b[i]%p;
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
}

using namespace Poly;

const int MAXK=3e4+5;

ll n;
int k;
int fac[MAXK],invfac[MAXK];
int bas[MAXK];

inline void Init(reg int n){
	fac[0]=bas[0]=1;
	for(reg int i=1;i<=n;++i){
		fac[i]=1ll*fac[i-1]*i%p;
		bas[i]=add(bas[i-1],bas[i-1]);
	}
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	return;
}

inline poly solve(reg int n){
	if(n==1){
		poly res;
		res.resize(k+1);
		res[0]=0;
		for(reg int i=1;i<=k;++i)
			res[i]=invfac[i];
		return res;
	}
	poly res,a;
	reg int tmp=n>>1;
	res=solve(tmp);
	a.resize(k+1);
	for(reg int i=1,pod=bas[tmp];i<=k;++i,pod=1ll*pod*bas[tmp]%p)
		a[i]=1ll*res[i]*pod%p;
	res=mul(res,a);
	res.resize(k+1);
	if(n&1){
		for(reg int i=1,pod=2;i<=k;++i,pod=add(pod,pod)){
			res[i]=1ll*res[i]*pod%p;
			a[i]=invfac[i];
		}
		res=mul(res,a);
		res.resize(k+1);
	}
	return res;
}

int main(void){
	n=readll(),k=read();
	Init(k);
	poly res=solve(n);
	reg int ans=0;
	for(reg int i=n;i<=k;++i)
		ans=add(ans,1ll*res[i]*fac[k]%p*invfac[k-i]%p);
	printf("%d\n",ans);
	return 0;
}