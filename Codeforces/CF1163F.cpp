#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXQ=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
};

int n,m,q;
Edge E[MAXM];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],id[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int Id){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len,id[cnt]=Id;
	head[u]=cnt;
	return;
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

bool vis[MAXN];
int las[MAXN];
ll disS[MAXN],disT[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
int l[MAXN],r[MAXN];
bool isG[MAXN];

inline void dijkstra(reg int s,reg ll dis[],reg int f){
	fill(vis+1,vis+n+1,false);
	fill(dis+1,dis+n+1,inf);
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
				las[v]=id[i];
				dis[v]=dis[u]+w[i];
				if(f==1&&!isG[v])
					l[v]=l[u];
				if(f==2&&!isG[v])
					r[v]=r[u];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

int pos[MAXM];
int tot;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll Min;
		#define Min(x) unit[(x)].Min
	};
	Node unit[MAXM<<2];
	inline void build(reg int k,reg int l,reg int r){
		Min(k)=inf;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Min(k)=min(Min(k),val);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return Min(k);
		if(pos<=mid)
			return min(Min(k),query(lson,l,mid,pos));
		else
			return min(Min(k),query(rson,mid+1,r,pos));
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i){
		E[i].u=read(),E[i].v=read(),E[i].w=read();
		Add_Edge(E[i].u,E[i].v,E[i].w,i),Add_Edge(E[i].v,E[i].u,E[i].w,i);
		pos[i]=-1;
	}
	dijkstra(n,disT,0);
	reg int ptr=1;
	isG[ptr]=true,l[ptr]=r[ptr]=tot;
	while(ptr!=n){
		reg int id=las[ptr];
		pos[id]=++tot;
		ptr^=E[id].u^E[id].v;
		isG[ptr]=true,l[ptr]=r[ptr]=tot;
	}
	dijkstra(1,disS,1),dijkstra(n,disT,2);
	SegmentTree::build(1,1,tot);
	for(reg int i=1;i<=m;++i)
		if(pos[i]==-1){
			if(l[E[i].u]<r[E[i].v])
				SegmentTree::update(1,1,tot,l[E[i].u]+1,r[E[i].v],disS[E[i].u]+E[i].w+disT[E[i].v]);
			if(l[E[i].v]<r[E[i].u])
				SegmentTree::update(1,1,tot,l[E[i].v]+1,r[E[i].u],disS[E[i].v]+E[i].w+disT[E[i].u]);
		}
	while(q--){
		static int t,x;
		t=read(),x=read();
		if(pos[t]!=-1)
			if(x<=E[t].w)
				writeln(disS[n]-E[t].w+x);
			else
				writeln(min(disS[n]-E[t].w+x,SegmentTree::query(1,1,tot,pos[t])));
		else
			if(x<E[t].w)
				writeln(min(disS[n],min(disS[E[t].u]+x+disT[E[t].v],disS[E[t].v]+x+disT[E[t].u])));
			else
				writeln(disS[n]);
	}
	flush();
	return 0;
}