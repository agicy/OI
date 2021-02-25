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

const int MAXN=2e5+5;
const int MAXM=3e5+5;
const int MAXQ=5e5+5;
const int inf=0x3f3f3f3f;

struct querys{
	int opt,v;
};

int n,m,q;
int p[MAXN];
int u[MAXM],v[MAXM];
bool vis[MAXM];
querys Q[MAXQ];

const int MAXV=2*MAXN;
const int MAXE=MAXV;
const int MAXLOG2V=19+1;

namespace UnionFind{
	int fa[MAXV];
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
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int t[MAXV];
int fa[MAXV][MAXLOG2V],dep[MAXV];
int tim,lef[MAXV],rig[MAXV];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	lef[u]=++tim;
	for(reg int i=1;i<MAXLOG2V;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v,u);
	}
	rig[u]=tim;
	return;
}

inline int getRt(reg int u,reg int x){
	for(reg int i=MAXLOG2V-1;i>=0;--i)
		if(t[fa[u][i]]>x)
			u=fa[u][i];
	return u;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,pos;
		#define Max(x) unit[(x)].Max
		#define pos(x) unit[(x)].pos
	};
	inline Node operator+(const Node& a,const Node& b){
		if(a.Max>b.Max)
			return a;
		else
			return b;
	}
	Node unit[MAXV<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Max(k)=val,pos(k)=l;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!k)exit(k);
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	for(reg int i=1;i<=m;++i)
		u[i]=read(),v[i]=read();
	for(reg int i=1;i<=q;++i){
		Q[i].opt=read(),Q[i].v=read();
		if(Q[i].opt==2)
			vis[Q[i].v]=true;
	}
	reg int tot=n;
	UnionFind::Init(n<<1);
	for(reg int i=1;i<=m;++i)
		if(!vis[i]&&!UnionFind::search(u[i],v[i])){
			reg int k=++tot;
			t[k]=inf;
			reg int x=UnionFind::find(u[i]),y=UnionFind::find(v[i]);
			Add_Edge(k,x),Add_Edge(k,y);
			UnionFind::merge(k,x),UnionFind::merge(k,y);
		}
	for(reg int i=q;i>=1;--i)
		if(Q[i].opt==2&&!UnionFind::search(u[Q[i].v],v[Q[i].v])){
			reg int k=++tot;
			t[k]=i;
			reg int x=UnionFind::find(u[Q[i].v]),y=UnionFind::find(v[Q[i].v]);
			Add_Edge(k,x),Add_Edge(k,y);
			UnionFind::merge(k,x),UnionFind::merge(k,y);
		}
	t[0]=-inf;
	for(reg int i=tot;i>=1;--i)
		if(!lef[i])
			dfs(i,0);
	for(reg int i=1;i<=n;++i)
		SegmentTree::update(1,1,tim,lef[i],p[i]);
	for(reg int i=1;i<=q;++i)
		if(Q[i].opt==1){
			reg int rt=getRt(Q[i].v,i);
			SegmentTree::Node res=SegmentTree::query(1,1,tim,lef[rt],rig[rt]);
			SegmentTree::update(1,1,tim,res.pos,0);
			writeln(res.Max);
		}
	flush();
	return 0;
}