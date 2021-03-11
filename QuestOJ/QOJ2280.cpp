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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXA=1e5+5;
const int MAXB=1e5+5;
const int bound=15;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN],Maxa=-inf,Mina=inf;
int b[MAXN],Maxb=-inf,Minb=inf;
int Ta[MAXA],Tb[MAXB];

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
		if(las==limit)
			return limit;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		las=limit;
		return limit;
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

int ans[MAXA+MAXB];

inline void solve(reg int k){
	poly a,b;
	a.resize(Maxa+1),b.resize(Maxb+1);
	for(reg int i=Mina;i<=Maxa;++i)
		a[i]=(Ta[i]>=k);
	for(reg int i=Minb;i<=Maxb;++i)
		b[i]=(Tb[i]>=k);
	poly res=mul(a,b);
	for(reg int i=Mina+Minb;i<=Maxa+Maxb;++i)
		ans[i]+=res[i];
	return;
}

int cnta,Qa[MAXN];
int cntb,Qb[MAXN];

inline void solve(void){
	for(reg int i=1;i<=cnta;++i)
		for(reg int j=1;j<=cntb;++j)
			ans[Qa[i]+Qb[j]]+=min(Ta[Qa[i]],Tb[Qb[j]])-bound;
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),Maxa=max(Maxa,a[i]),Mina=min(Mina,a[i]);
	for(reg int i=1;i<=n;++i)
		b[i]=read(),Maxb=max(Maxb,b[i]),Minb=min(Minb,b[i]);
	for(reg int i=1;i<=n;++i)
		++Ta[a[i]];
	for(reg int i=1;i<=n;++i)
		++Tb[b[i]];
	for(reg int i=Mina;i<=Maxa;++i)
		if(Ta[i]>=bound)
			Qa[++cnta]=i;
	for(reg int i=Minb;i<=Maxb;++i)
		if(Tb[i]>=bound)
			Qb[++cntb]=i;
	for(reg int i=1;i<=bound;++i)
		solve(i);
	solve();
	reg int Max=0;
	for(reg int i=Mina+Minb;i<=Maxa+Maxb;++i)
		Max=max(Max,ans[i]);
	printf("%d\n",Max);
	return 0;
}