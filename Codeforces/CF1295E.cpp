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

const int MAXN=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll Min,tag;
		#define Min(x) unit[(x)].Min
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void add(reg int k,reg ll val){
		Min(k)+=val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			add(lson,tag(k)),add(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n;
int p[MAXN],a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		SegmentTree::update(1,0,n,p[i],n,a[i]);
	reg ll ans=inf;
	for(reg int i=1;i<n;++i){
		SegmentTree::update(1,0,n,p[i],n,-a[i]);
		SegmentTree::update(1,0,n,0,p[i]-1,a[i]);
		ans=min(ans,SegmentTree::Min(1));
	}
	printf("%lld\n",ans);
	return 0;
}