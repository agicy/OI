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

const int MAXN=3e5+5;
const int MAXM=3e5+5;

int n,m;
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
		int sum;
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			sum(k)+=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
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

inline int query(int x,int y){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=SegmentTree::query(1,1,n,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	if(dfn[x]<dfn[y])
		res+=SegmentTree::query(1,1,n,dfn[x]+1,dfn[y]);
	return res;
}

int tot;
pair<int,int> W[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int p,q;
		p=read(),q=read();
		Add_Edge(p,q);
		Add_Edge(q,p);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	while(m--){
		static char opt;
		static int p,q;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'C':{
				p=read(),q=read();
				W[++tot]=make_pair(p,q);
				reg int son=dep[p]<dep[q]?q:p;
				SegmentTree::update(1,1,n,dfn[son],1);
				break;
			}
			case 'Q':{
				p=read(),q=read();
				reg int res=query(p,q);
				puts(res?"No":"Yes");
				break;
			}
			case 'U':{
				p=read();
				reg int x=W[p].first,y=W[p].second;
				reg int son=dep[x]<dep[y]?y:x;
				SegmentTree::update(1,1,n,dfn[son],-1);
				break;
			}
		}
	}
	return 0;
}