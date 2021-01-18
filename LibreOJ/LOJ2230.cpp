#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
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

const int MAXN=1e5+5;
const int MAXQ=1e5+5;

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN];
int tim,dfn[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	dfn[u]=++tim;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

namespace SegmentTree{
	const int MAXSIZE=40*MAXN;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int k){
		sum(k)=sum(lson(k))+sum(rson(k));
		return;
	}
	inline void build(reg int &k,reg int l,reg int r,reg int pos){
		if(!k)
			k=++tot;
		if(l==r){
			++sum(k);
			return;
		}
		if(pos<=mid)
			build(lson(k),l,mid,pos);
		else
			build(rson(k),mid+1,r,pos);
		pushup(k);
		return;
	}
	inline void merge(reg int &p,reg int &q,reg int l,reg int r){
		if(!p||!q){
			p|=q;
			return;
		}
		if(l==r){
			sum(p)+=sum(q);
			return;
		}
		merge(lson(p),lson(q),l,mid),merge(rson(p),rson(q),mid+1,r);
		pushup(p);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!k)
			return 0;
		if(L<=l&&r<=R)
			return sum(k);
		if(L<=mid&&mid<R)
			return query(lson(k),l,mid,L,R)+query(rson(k),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(k),l,mid,L,R);
		else
			return query(rson(k),mid+1,r,L,R);
	}
}

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
}

struct querys{
	char opt;
	int x,y;
};

int n,q;
querys Q[MAXQ];
int rt[MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=q;++i){
		do
			Q[i].opt=getchar();
		while(!isalpha(Q[i].opt));
		Q[i].x=read(),Q[i].y=read();
		if(Q[i].opt=='A'){
			Add_Edge(Q[i].x,Q[i].y);
			Add_Edge(Q[i].y,Q[i].x);
		}
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			dfs(i,0);
	UnionFind::Init(n);
	for(reg int i=1;i<=n;++i)
		SegmentTree::build(rt[i],1,n,dfn[i]);
	for(reg int i=1;i<=q;++i)
		switch(Q[i].opt){
			case 'A':{
				SegmentTree::merge(rt[UnionFind::find(Q[i].x)],rt[UnionFind::find(Q[i].y)],1,n);
				UnionFind::merge(Q[i].x,Q[i].y);
				break;
			}
			case 'Q':{
				reg int son=(dep[Q[i].x]<dep[Q[i].y])?Q[i].y:Q[i].x;
				reg int r=UnionFind::find(son);
				reg int ans1=SegmentTree::query(rt[r],1,n,dfn[son],dfn[son]+siz[son]-1);
				reg int ans2=((1<=dfn[son]-1)?SegmentTree::query(rt[r],1,n,1,dfn[son]-1):0)+((dfn[son]+siz[son]<=n)?SegmentTree::query(rt[r],1,n,dfn[son]+siz[son],n):0);
				writeln(1ll*ans1*ans2);
				break;
			}
		}
	flush();
	return 0;
}