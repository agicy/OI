#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=2e4+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m;
ll d[MAXN],c[MAXN],s[MAXN],w[MAXN];
int st[MAXN],ed[MAXN];
ll f[MAXN];
vector<int> G[MAXN];

inline void Add_Edge(reg int u,int v){
	G[u].push_back(v);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll Min;
		ll tAdd;
		#define Min(x) unit[(x)].Min
		#define tAdd(x) unit[(x)].tAdd
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg ll a[]){
		tAdd(k)=0;
		if(l==r){
			Min(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg ll val){
		Min(k)+=val,tAdd(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tAdd(k)){
			add(lson,tAdd(k)),add(rson,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L>R)
			return;
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
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L>R)
			return inf;
		if(L<=l&&r<=R)
			return Min(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=2;i<=n;++i)
		d[i]=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=n;++i)
		s[i]=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	++n,++m;
	d[n]=w[n]=inf;
	for(reg int i=1;i<=n;++i){
		st[i]=lower_bound(d+1,d+n+1,d[i]-s[i])-d,ed[i]=upper_bound(d+1,d+n+1,d[i]+s[i])-d-1;
		Add_Edge(ed[i],i);
	}
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		f[i]=sum+c[i];
		for(int v:G[i])
			sum+=w[v];
	}
	reg ll res=f[n];
	for(reg int i=2;i<=m;++i){
		SegmentTree::build(1,1,n,f);
		for(reg int j=1;j<=n;++j){
			f[j]=SegmentTree::query(1,1,n,1,j-1)+c[j];
			for(int v:G[j])
				SegmentTree::update(1,1,n,1,st[v]-1,w[v]);
		}
		res=min(res,f[n]);
	}
	printf("%lld\n",res);
	return 0;
}