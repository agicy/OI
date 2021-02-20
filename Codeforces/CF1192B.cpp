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

const int MAXN=1e5+5;
const int MAXQ=1e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll dMax,dMin,lefD,rigD,Max,tag;
		#define dMax(x) unit[(x)].dMax
		#define dMin(x) unit[(x)].dMin
		#define lefD(x) unit[(x)].lefD
		#define rigD(x) unit[(x)].rigD
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k){
		dMax(k)=max(dMax(lson),dMax(rson)),dMin(k)=max(dMin(lson),dMin(rson));
		lefD(k)=max(max(lefD(lson),lefD(rson)),dMax(lson)+dMin(rson)),rigD(k)=max(max(rigD(lson),rigD(rson)),dMin(lson)+dMax(rson));
		Max(k)=max(max(Max(lson),Max(rson)),max(lefD(lson)+dMax(rson),dMax(lson)+rigD(rson)));
		return;
	}
	inline void add(reg int k,reg ll val){
		dMax(k)+=val,dMin(k)-=(val<<1);
		lefD(k)-=val,rigD(k)-=val;
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
	inline void build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			dMax(k)=a[l],dMin(k)=-(a[l]<<1);
			lefD(k)=rigD(k)=-a[l];
			Max(k)=0;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
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

int n,q;
int a[MAXN],b[MAXN];
ll c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
ll w[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

ll dis[MAXN];
int tim,lef[MAXN],rig[MAXN],rnk[MAXN<<1];

inline void dfs(reg int u,reg int father){
	rnk[lef[u]=++tim]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dis[v]=dis[u]+w[i];
			dfs(v,u);
			rnk[++tim]=u;
		}
	}
	rig[u]=tim;
	return;
}

int main(void){
	reg ll w;
	n=read(),q=read(),w=readll();
	for(reg int i=1;i<n;++i){
		a[i]=read(),b[i]=read(),c[i]=readll();
		Add_Edge(a[i],b[i],c[i]),Add_Edge(b[i],a[i],c[i]);
	}
	dfs(1,0);
	static ll tmp[MAXN<<1];
	for(reg int i=1;i<=tim;++i)
		tmp[i]=dis[rnk[i]];
	SegmentTree::build(1,1,tim,tmp);
	reg ll lastans=0;
	while(q--){
		static int d;
		static ll e;
		d=(read()+lastans)%(n-1)+1,e=(readll()+lastans)%w;
		reg int son=dis[a[d]]<dis[b[d]]?b[d]:a[d];
		SegmentTree::update(1,1,tim,lef[son],rig[son],e-c[d]);
		c[d]=e;
		printf("%lld\n",lastans=SegmentTree::Max(1));
	}
	return 0;
}