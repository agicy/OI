#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef pair<ll,int> PLI;
const ll INF=1e18;
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
const PLI inf=make_pair(INF,0);

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		PLI p[2];
		ll tag;
		#define p(k) unit[(k)].p
		#define tag(k) unit[(k)].tag
	};
	Node unit[MAXN<<2];
	using namespace UnionFind;
	inline void cMax(reg int k,const PLI& son){
		if(son.first<p(k)[0].first){
			if(son.second!=p(k)[0].second)
				p(k)[1]=p(k)[0];
			p(k)[0]=son;
		}
		else if(son.first<p(k)[1].first&&son.second!=p(k)[0].second)
			p(k)[1]=son;
		return;
	}
	inline void pushup(reg int k){
		p(k)[0]=p(k)[1]=inf;
		cMax(k,p(lson)[0]),cMax(k,p(lson)[1]);
		cMax(k,p(rson)[0]),cMax(k,p(rson)[1]);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tag(k)=0;
		if(l==r){
			p(k)[0]=make_pair(0,find(l));
			p(k)[1]=inf;
			return;
		}
		build(lson,l,mid);
		build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg ll val){
		tag(k)+=val;
		p(k)[0].first+=val;
		p(k)[1].first+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			add(lson,tag(k));
			add(rson,tag(k));
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

struct Line{
	int x,l,r;
	ll val;
	inline Line(reg int x=0,reg int l=0,reg int r=0,reg ll val=0):x(x),l(l),r(r),val(val){
		return;
	}
	inline bool operator<(const Line& a)const{
		return x<a.x;
	}
};

int n,m;
Line L[MAXM<<2];
PLI edge[MAXN];

int main(void){
	using namespace UnionFind;
	using namespace SegmentTree;
	n=read(),m=read();
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		static int l1,r1,l2,r2;
		static ll w;
		l1=read(),r1=read(),l2=read(),r2=read(),w=read();
		L[++tot]=Line(l1,l2,r2,w);
		L[++tot]=Line(l2,l1,r1,w);
		if(r1<n)
			L[++tot]=Line(r1+1,l2,r2,-w);
		if(r2<n)
			L[++tot]=Line(r2+1,l1,r1,-w);
	}
	sort(L+1,L+tot+1);
	Init(n);
	reg int cnt=n;
	reg ll ans=0;
	PLI p;
	while(cnt>1){
		for(reg int i=1;i<=n;++i)
			edge[i]=inf;
		build(1,1,n);
		reg int ptr=1;
		for(reg int i=1;i<=n;++i){
			while(ptr<=tot&&L[ptr].x==i){
				update(1,1,n,L[ptr].l,L[ptr].r,L[ptr].val);
				++ptr;
			}
			reg int u=find(i);
			p=(unit[1].p[0].second==u)?unit[1].p[1]:unit[1].p[0];
			if(p.first<edge[u].first)
				edge[u]=p;
		}
		for(reg int i=1;i<=n;++i)
			if(edge[i].second&&!search(i,edge[i].second)){
				--cnt;
				ans+=edge[i].first;
				merge(i,edge[i].second);
			}
	}
	printf("%lld\n",ans);
	return 0;
}
