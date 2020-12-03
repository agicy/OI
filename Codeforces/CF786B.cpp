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

const int MAXN=1e5+5;
const int MAXV=5e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

int n,q,s;
vector<pair<int,int>/**/> G[MAXV];

inline void Add_Edge(reg int u,reg int v,reg int len){
	G[u].push_back(make_pair(v,len));
	return;
}

namespace utdSegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot;
	struct Node{
		int id;
		#define id(x) unit[(x)].id
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		id(k)=++tot;
		if(l==r){
			Add_Edge(id(k),l,0);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		Add_Edge(id(k),id(lson),0),Add_Edge(id(k),id(rson),0);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Id,reg int w){
		if(L<=l&&r<=R){
			Add_Edge(Id,id(k),w);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,Id,w);
		if(R>mid)
			update(rson,mid+1,r,L,R,Id,w);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef id
}

namespace dtuSegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot;
	struct Node{
		int id;
		#define id(x) unit[(x)].id
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		id(k)=++tot;
		if(l==r){
			Add_Edge(l,id(k),0);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		Add_Edge(id(lson),id(k),0),Add_Edge(id(rson),id(k),0);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Id,reg int w){
		if(L<=l&&r<=R){
			Add_Edge(id(k),Id,w);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,Id,w);
		if(R>mid)
			update(rson,mid+1,r,L,R,Id,w);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef id
}

struct Node{
	int id;
	ll dis;
	inline Node(reg int id=0,reg ll dis=0):id(id),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXV];
ll dis[MAXV];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		for(auto p:G[u]){
			reg int v=p.first,w=p.second;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

int main(void){
	n=read(),q=read(),s=read();
	utdSegmentTree::tot=n;
	utdSegmentTree::build(1,1,n);
	dtuSegmentTree::tot=utdSegmentTree::tot;
	dtuSegmentTree::build(1,1,n);
	while(q--){
		static int opt,v,u,w,l,r;
		opt=read();
		switch(opt){
			case 1:{
				v=read(),u=read(),w=read();
				Add_Edge(v,u,w);
				break;
			}
			case 2:{
				v=read(),l=read(),r=read(),w=read();
				utdSegmentTree::update(1,1,n,l,r,v,w);
				break;
			}
			case 3:{
				v=read(),l=read(),r=read(),w=read();
				dtuSegmentTree::update(1,1,n,l,r,v,w);
				break;
			}
		}
	}
	dijkstra(s);
	for(reg int i=1;i<=n;++i)
		printf("%lld%c",dis[i]==inf?-1:dis[i],i==n?'\n':' ');
	return 0;
}