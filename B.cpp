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

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXM=4e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Graph{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int id;
		ll val;
		inline Node(reg int id=0,reg ll val=0):id(id),val(val){
			return;
		}
		inline bool operator<(const Node& a)const{
			return val<a.val;
		}
		inline bool operator>(const Node& a)const{
			return val>a.val;
		}
	};
	bool vis[MAXN];
	ll dis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void dijkstra(reg int s){
		memset(vis,false,sizeof(vis));
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0,Q.push(Node(s,dis[s]));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.id;
			if(vis[u])
				continue;
			vis[u]=true;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>dis[u]+w[i]){
					dis[v]=dis[u]+w[i];
					Q.push(Node(v,dis[v]));
				}
			}
		}
		return;
	}
};

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Line{
		ll k,b;
		inline Line(reg ll k=0,reg ll b=0):k(k),b(b){
			return;
		}
	};
	inline ll getVal(const Line& a,reg int x){
		return a.k*x+a.b;
	}
	struct Node{
		Line val;
		bool tag;
		#define val(x) unit[(x)].val
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void update(reg int k,reg int l,reg int r,Line Val){
		if(!tag(k)){
			tag(k)=true;
			val(k)=Val;
			return;
		}
		reg ll lef=getVal(val(k),l),rig=getVal(val(k),r);
		reg ll tmpl=getVal(Val,l),tmpr=getVal(Val,r);
		if(lef<=tmpl&&rig<=tmpr)
			return;
		if(tmpl<lef&&tmpr<rig){
			swap(val(k),Val);
			return;
		}
		reg ll midv=getVal(val(k),mid),tmpv=getVal(Val,mid);
		if(midv<=tmpv){
			if(tmpl<lef)
				update(lson,l,mid,Val);
			else
				update(rson,mid+1,r,Val);
		}
		else{
			swap(val(k),Val);
			if(lef<=tmpl)
				update(lson,l,mid,Val);
			else
				update(rson,mid+1,r,Val);
		}
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int x){
		reg ll res=inf;
		if(tag(k))
			res=min(res,getVal(val(k),x));
		if(l==r)
			return res;
		if(x<=mid)
			res=min(res,query(lson,l,mid,x));
		else
			res=min(res,query(rson,mid+1,r,x));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m,s,t;
Graph Gs,Gt;

int main(void){
	n=read(),m=read(),s=read(),t=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Gs.Add_Edge(u,v,w),Gt.Add_Edge(v,u,w);
	}
	Gs.dijkstra(s),Gt.dijkstra(t);
	reg ll ans=min(Gs.dis[t],Gt.dis[s]);
	for(reg int i=1;i<=n;++i)
		if(Gt.dis[i]!=inf)
			SegmentTree::update(1,1,n,SegmentTree::Line(-2ll*i,Gt.dis[i]+1ll*i*i));
	for(reg int i=1;i<=n;++i)
		if(Gs.dis[i]!=inf)
			ans=min(ans,Gs.dis[i]+1ll*i*i+SegmentTree::query(1,1,n,i));
	printf("%lld\n",ans);
	return 0;
}