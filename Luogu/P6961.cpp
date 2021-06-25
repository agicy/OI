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

const int MAXN=3e3+5;
const int MAXM=3e3+5;

struct Edge{
	int u,v,w;
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m,k;
Edge e[MAXM];

namespace Graph{
	struct Edge{
		int v,w;
		inline Edge(reg int v=0,reg int w=0):v(v),w(w){
			return;
		}
	};
	vector<Edge> G[MAXN];
	inline void Init(void){
		for(reg int i=1;i<=n;++i)
			G[i].clear();
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg int w){
		G[u].push_back(Edge(v,w));
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int w){
		Add_Edge(u,v,w),Add_Edge(v,u,w);
		return;
	}
	const ll inf=0x3f3f3f3f3f3f3f3f;

	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int id;
			ll val;
			#define id(x) unit[(x)].id
			#define val(x) unit[(x)].val
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			if(val(lson)<val(rson))
				unit[k]=unit[lson];
			else
				unit[k]=unit[rson];
			return;
		}
		inline void build(reg int k,reg int l,reg int r){
			if(l==r){
				id(k)=l,val(k)=inf;
				return;
			}
			build(lson,l,mid),build(rson,mid+1,r);
			pushup(k);
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int pos,reg ll Val){
			if(l==r){
				val(k)=min(val(k),Val);
				return;
			}
			if(pos<=mid)
				update(lson,l,mid,pos,Val);
			else
				update(rson,mid+1,r,pos,Val);
			pushup(k);
			return;
		}
		inline void del(reg int k,reg int l,reg int r,reg int pos){
			if(l==r){
				val(k)=inf;
				return;
			}
			if(pos<=mid)
				del(lson,l,mid,pos);
			else
				del(rson,mid+1,r,pos);
			pushup(k);
			return;
		}
		#undef lson
		#undef rson
		#undef mid
	}
	bool vis[MAXN];
	inline ll dijkstra(reg int s,reg int t){
		fill(vis+1,vis+n+1,false);
		SegmentTree::build(1,1,n);
		SegmentTree::update(1,1,n,s,0);
		while(true){
			reg int u=SegmentTree::unit[1].id;
			reg ll dis=SegmentTree::unit[1].val;
			vis[u]=true;
			SegmentTree::del(1,1,n,u);
			if(u==t)
				return dis;
			for(Edge e:G[u])
				if(!vis[e.v])
					SegmentTree::update(1,1,n,e.v,dis+e.w);
		}
		return -1;
	}
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		e[i].u=read(),e[i].v=read(),e[i].w=read();
		Graph::Add_Tube(e[i].u,e[i].v,e[i].w);
	}
	sort(e+1,e+m+1);
	reg ll ans=Graph::dijkstra(1,n);
	for(reg int i=1;i<=m;++i){
		Graph::Init();
		for(reg int j=1;j<=i;++j)
				Graph::Add_Tube(e[j].u,e[j].v,0);
		for(reg int j=i+1;j<=m;++j)
			Graph::Add_Tube(e[j].u,e[j].v,e[j].w-e[i].w);
		ans=min(ans,Graph::dijkstra(1,n)+1ll*k*e[i].w);
	}
	printf("%lld\n",ans);
	return 0;
}