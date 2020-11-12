#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXK=32;

int n,m,K;
int w[MAXN];
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
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	rnk[tim]=u;
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
	struct Chunk{
		bitset<MAXK> x[2];
	};
	inline Chunk operator+(const Chunk& a,const Chunk& b){
		static Chunk res;
		for(reg int i=0;i<K;++i){
			res.x[0][i]=b.x[a.x[0][i]][i];
			res.x[1][i]=b.x[a.x[1][i]][i];
		}
		return res;
	}
	struct Node{
		Chunk lef,rig;
		#define lef(x) unit[(x)].lef
		#define rig(x) unit[(x)].rig
	};
	inline Node operator+(const Node& a,const Node& b){
		static Node res;
		res.lef=a.lef+b.lef;
		res.rig=b.rig+a.rig;
		return res;
	}
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			reg int id=rnk[l];
			for(reg int i=0;i<K;++i){
				unit[k].lef.x[0][i]=unit[k].rig.x[0][i]=1;
				unit[k].lef.x[1][i]=unit[k].rig.x[1][i]=(((w[id]>>i)&1)^1);
			}
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			for(reg int i=0;i<K;++i){
				unit[k].lef.x[0][i]=unit[k].rig.x[0][i]=1;
				unit[k].lef.x[1][i]=unit[k].rig.x[1][i]=(((val>>i)&1)^1);
			}
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Chunk queryLtoR(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].lef;
		if(L<=mid&&mid<R){
			Chunk le=queryLtoR(lson,l,mid,L,R),ri=queryLtoR(rson,mid+1,r,L,R);
			return le+ri;
		}
		else if(L<=mid)
			return queryLtoR(lson,l,mid,L,R);
		else
			return queryLtoR(rson,mid+1,r,L,R);
	}
	inline Chunk queryRtoL(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].rig;
		if(L<=mid&&mid<R){
			Chunk le=queryRtoL(lson,l,mid,L,R),ri=queryRtoL(rson,mid+1,r,L,R);
			return ri+le;
		}
		else if(L<=mid)
			return queryRtoL(lson,l,mid,L,R);
		else
			return queryRtoL(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline uint query(reg int x,reg int y){
	static SegmentTree::Chunk ansl,ansr;
	for(reg int i=0;i<K;++i)
		ansl.x[0][i]=ansr.x[0][i]=0,ansl.x[1][i]=ansr.x[1][i]=1;
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]]){
			ansl=ansl+SegmentTree::queryRtoL(1,1,n,dfn[top[x]],dfn[x]);
			x=fa[top[x]];
		}
		else{
			ansr=SegmentTree::queryLtoR(1,1,n,dfn[top[y]],dfn[y])+ansr;
			y=fa[top[y]];
		}
	if(dep[x]<=dep[y])
		ansl=ansl+SegmentTree::queryLtoR(1,1,n,dfn[x],dfn[y]);
	else
		ansr=SegmentTree::queryRtoL(1,1,n,dfn[y],dfn[x])+ansr;
	ansl=ansl+ansr;
	reg uint res=0;
	for(reg int i=0;i<K;++i)
		if(ansl.x[0][i])
			res|=(1u<<i);
	return res;
}

int main(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	SegmentTree::build(1,1,n);
	while(m--){
		static char opt;
		static int x,y;
		do
			opt=getchar();
		while(!isalpha(opt));
		x=read(),y=read();
		switch(opt){
			case 'R':{
				reg int pos=dfn[x];
				SegmentTree::update(1,1,n,pos,y);
				break;
			}
			case 'Q':{
				reg uint res=query(x,y);
				printf("%u\n",res);
				break;
			}
		}
	}
	return 0;
}