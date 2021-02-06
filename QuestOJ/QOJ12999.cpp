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

const int MAXN=5e4+5;
const int inf=0x3f3f3f3f;

int n;
int p[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int top[MAXN];
int tim,dfn[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,Min,lMax,rMax;
		int tag;
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		res.Max=max(a.Max,b.Max);
		res.Min=min(a.Min,b.Min);
		res.lMax=max(a.Max-b.Min,max(a.lMax,b.lMax));
		res.rMax=max(b.Max-a.Min,max(b.rMax,a.rMax));
		res.tag=0;
		return res;
	}
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			Max(k)=Min(k)=a[l];
			lMax(k)=rMax(k)=tag(k)=0;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int val){
		tag(k)+=val;
		Max(k)+=val,Min(k)+=val;
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
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		Node res;
		if(L<=l&&r<=R){
			res=unit[k];
			add(k,val);
			return res;
		}
		pushdown(k);
		if(L<=mid&&mid<R){
			res=query(lson,l,mid,L,R,val)+query(rson,mid+1,r,L,R,val);
			pushup(k);
			return res;
		}
		else if(L<=mid){
			res=query(lson,l,mid,L,R,val);
			pushup(k);
			return res;
		}
		else{
			res=query(rson,mid+1,r,L,R,val);
			pushup(k);
			return res;
		}
	}
	#undef lson
	#undef rson
	#undef mid
}

inline int query(reg int x,reg int y,reg int val){
	SegmentTree::Node l,r;
	l.Max=r.Max=-inf,l.Min=r.Min=inf,l.lMax=l.rMax=l.tag=r.lMax=r.rMax=r.tag=0;
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]]){
			l=SegmentTree::query(1,1,n,dfn[top[x]],dfn[x],val)+l;
			x=fa[top[x]];
		}
		else{
			r=SegmentTree::query(1,1,n,dfn[top[y]],dfn[y],val)+r;
			y=fa[top[y]];
		}
	if(dep[x]>dep[y])
		l=SegmentTree::query(1,1,n,dfn[y],dfn[x],val)+l;
	else
		r=SegmentTree::query(1,1,n,dfn[x],dfn[y],val)+r;
	swap(l.lMax,l.rMax);
	return (l+r).rMax;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	dfs1(1,0),dfs2(1,0,1);
	static int val[MAXN];
	for(reg int i=1;i<=n;++i)
		val[dfn[i]]=p[i];
	SegmentTree::build(1,1,n,val);
	reg int q=read();
	while(q--){
		static int a,b,v;
		a=read(),b=read(),v=read();
		writeln(query(a,b,v));
	}
	flush();
	return 0;
}