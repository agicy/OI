#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];

inline void dfs1(reg int u,reg int father){
	size[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			size[u]+=size[v];
			if(size[son[u]]<size[v])
				son[u]=v;
		}
	}
	return;
}

int tim,dfn[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	dfn[u]=++tim;
	top[u]=topf;
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
		bool val;
		int tag;
		#define val(x) unit[(x)].val
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		val(k)=val(lson)||val(rson);
		return;
	}
	inline void set0(reg int k){
		val(k)=false;
		tag(k)=0;
		return;
	}
	inline void set1(reg int k){
		val(k)=true;
		tag(k)=1;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)==0){
			set0(lson);
			set0(rson);
			tag(k)=-1;
		}
		if(tag(k)==1){
			set1(lson);
			set1(rson);
			tag(k)=-1;
		}
		return;
	}
	inline void update0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			set0(k);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update0(lson,l,mid,L,R);
		if(R>mid)
			update0(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline void update1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			set1(k);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update1(lson,l,mid,L,R);
		if(R>mid)
			update1(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline bool query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return val(k);
		pushdown(k);
		if(pos<=mid)
			return query(lson,l,mid,pos);
		else
			return query(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void updateSubtree(reg int u){
	SegmentTree::update1(1,1,n,dfn[u],dfn[u]+size[u]-1);
	return;
}

inline void updatePath(reg int u){
	while(top[u]!=1){
		SegmentTree::update0(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	SegmentTree::update0(1,1,n,1,dfn[u]);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	m=read();
	while(m--){
		static int opt,u;
		opt=read(),u=read();
		switch(opt){
			case 1:{
				updateSubtree(u);
				break;
			}
			case 2:{
				updatePath(u);
				break;
			}
			case 3:{
				printf("%d\n",SegmentTree::query(1,1,n,dfn[u]));
				break;
			}
		}
	}
	return 0;
}