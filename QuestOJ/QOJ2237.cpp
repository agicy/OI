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

namespace Poly{
	const int MAXSIZE=4e5+5;
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	typedef vector<int> poly;
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
	int r[MAXSIZE];
	inline int Init(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
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
	inline poly rev_mul(poly a,poly b){
		reg int l=a.size(),r=b.size();
		reverse(b.begin(),b.end());
		poly tmp=mul(a,b);
		poly res(l-r+1);
		for(reg int i=0;i<=l-r;++i)
			res[i]=tmp[r-1+i];
		return res;
	}
}

using namespace Poly;

const int MAXN=1e5+5;

int n;
int a[MAXN];
int pi[MAXN];
int ans[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	poly val[MAXN<<2],t[MAXN<<2];
	inline void pushup(reg int k){
		val[k]=mul(val[lson],val[rson]);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			val[k]=poly{(p+1-pi[l])%p,pi[l]};
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void query(reg int k,reg int l,reg int r){
		if(l==r){
			ans[l]=t[k][0];
			return;
		}
		t[lson]=rev_mul(t[k],val[rson]),t[rson]=rev_mul(t[k],val[lson]);
		query(lson,l,mid),query(rson,mid+1,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i){
		static int x,y;
		x=read(),y=read();
		pi[i]=1ll*x*pow(y,p-2,p)%p;
	}
	build(1,1,n);
	for(reg int i=0;i<n;++i)
		t[1].push_back(a[i]);
	query(1,1,n);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}