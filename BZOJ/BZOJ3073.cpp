#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e5+5;
const int MAXM=1e5+5;
const int MAXV=5*MAXN+4*MAXM;

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

int n,m,p;
int tot;
vector<Edge> G[MAXV];

inline void Add_Edge(reg int u,reg int v,reg int w){
	G[u].push_back(Edge(v,w));
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int id_up,id_dn;
		#define id_up(x) unit[(x)].id_up
		#define id_dn(x) unit[(x)].id_dn
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		id_up(k)=++tot,id_dn(k)=++tot;
		if(l==r){
			Add_Edge(id_dn(k),l,0);
			Add_Edge(l,id_up(k),0);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		Add_Edge(id_up(lson),id_up(k),0),Add_Edge(id_up(rson),id_up(k),0);
		Add_Edge(id_dn(k),id_dn(lson),0),Add_Edge(id_dn(k),id_dn(rson),0);
		return;
	}
	inline void update_up(reg int k,reg int l,reg int r,reg int L,reg int R,reg int v){
		if(L<=l&&r<=R){
			Add_Edge(id_up(k),v,0);
			return;
		}
		if(L<=mid)
			update_up(lson,l,mid,L,R,v);
		if(R>mid)
			update_up(rson,mid+1,r,L,R,v);
		return;
	}
	inline void update_dn(reg int k,reg int l,reg int r,reg int L,reg int R,reg int v){
		if(L<=l&&r<=R){
			Add_Edge(v,id_dn(k),0);
			return;
		}
		if(L<=mid)
			update_dn(lson,l,mid,L,R,v);
		if(R>mid)
			update_dn(rson,mid+1,r,L,R,v);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int dis[MAXV];
deque<int> Q;

inline void bfs(reg int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push_back(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop_front();
		for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
			reg int v=it->v,w=it->w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!w)
					Q.push_front(v);
				else
					Q.push_back(v);
			}
		}
	}
	return;
}

inline void Add_Edge(reg int l1,reg int r1,reg int l2,reg int r2){
	reg int p,q;
	p=++tot,q=++tot;
	SegmentTree::update_dn(1,1,n,l1,r1,p);
	Add_Edge(q,p,1);
	SegmentTree::update_up(1,1,n,l2,r2,q);
	p=++tot,q=++tot;
	SegmentTree::update_up(1,1,n,l1,r1,p);
	Add_Edge(p,q,1);
	SegmentTree::update_dn(1,1,n,l2,r2,q);
	return;
}

int main(void){
	n=read(),m=read(),p=read();
	tot=n;
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<=m;++i){
		static int a,b,c,d;
		a=read(),b=read(),c=read(),d=read();
		Add_Edge(a,b,c,d);
	}
	bfs(p);
	for(reg int i=1;i<=n;++i)
		writeln(dis[i]);
	flush();
	return 0;
}