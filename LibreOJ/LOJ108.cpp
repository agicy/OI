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
	typedef vector<int> poly;
	vector<int> r;
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
		r.resize(limit);
		for(reg int i=1;i<limit;++i)
			r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg poly& a,reg int limit,reg int type){
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
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=Init(s);
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

int n,m;
poly a,b;

int main(void){
	n=read()+1,m=read()+1;
	a.resize(n),b.resize(m);
	for(reg int i=0;i<n;++i)
		a[i]=read();
	for(reg int i=0;i<m;++i)
		b[i]=read();
	poly ans=mul(a,b);
	for(reg int i=0,size=ans.size();i<size;++i)
		printf("%d%c",ans[i],i==size-1?'\n':' ');
	return 0;
}