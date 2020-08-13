#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

inline ll calc0(reg ll n){
	return n;
}

inline ll calc0(reg ll l,reg ll r){
	return calc0(r)-calc0(l-1);
}

inline ll calc1(reg ll n){
	return n*(n+1)>>1;
}

inline ll calc1(reg ll l,reg ll r){
	return calc1(r)-calc1(l-1);
}

inline ll calc2(reg ll n){
	return n*(n+1)/2*(2*n+1)/3;
}

inline ll calc2(reg ll l,reg ll r){
	return calc2(r)-calc2(l-1);
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum[3];
		ll tag;
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)[0]=sum(lson)[0]+sum(rson)[0];
		sum(k)[1]=sum(lson)[1]+sum(rson)[1];
		sum(k)[2]=sum(lson)[2]+sum(rson)[2];
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg ll val){
		sum(k)[0]+=calc0(l,r)*val;
		sum(k)[1]+=calc1(l,r)*val;
		sum(k)[2]+=calc2(l,r)*val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			add(lson,l,mid,tag(k));
			add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	ll res0,res1,res2;
	inline void query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			res0+=sum(k)[0];
			res1+=sum(k)[1];
			res2+=sum(k)[2];
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			query(lson,l,mid,L,R);
		if(R>mid)
			query(rson,mid+1,r,L,R);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

using namespace SegmentTree;

int n,m;

int main(void){
	n=read(),m=read();
	while(m--){
		static char op;
		static ll l,r,v;
		do
			op=getchar();
		while(op!='C'&&op!='Q');
		l=read(),r=read()-1;
		switch(op){
			case 'C':{
				v=read();
				if(l>r)
					break;
				update(1,1,n,l,r,v);
				break;
			}
			case 'Q':{
				if(l>r)
					break;
				res0=res1=res2=0;
				query(1,1,n,l,r);
				reg ll ans1=(r-l+1-1ll*l*r)*res0+(l+r)*res1-res2;
				reg ll ans2=(r-l+2)*(r-l+1)/2;
				reg ll d=gcd(ans1,ans2);
				ans1/=d,ans2/=d;
				printf("%lld/%lld\n",ans1,ans2);
				break;
			}
		}
	}
	return 0;
}