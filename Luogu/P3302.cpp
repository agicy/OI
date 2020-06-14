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

const int MAXN=80000+5;
const int MAXLOG2N=17+1;
const int MAXM=80000+5;
const int MAXT=80000+5;

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
}

using UnionFind::Init;
using UnionFind::find;

int n,m,T;
int a[MAXN];
int b[MAXN];
int S;

inline int GetID(int x){
	return lower_bound(b+1,b+n+1,x)-b;
}

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot;
	int root[MAXN];
	const int MAXSIZE=MAXN*600;
	struct Node{
		int lson,rson;
		int val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define val(x) unit[(x)].val
	};
	Node unit[MAXSIZE];
	inline void Build(reg int &k,reg int l,reg int r){
		k=++tot;
		if(l!=r){
			Build(lson(k),l,mid);
			Build(rson(k),mid+1,r);
		}
		return;
	}
	inline void Update(reg int &k,reg int pre,reg int l,reg int r,reg int pos){
		k=++tot;
		unit[k]=unit[pre];
		++val(k);
		if(l!=r){
			if(pos<=mid)
				Update(lson(k),lson(pre),l,mid,pos);
			if(pos>mid)
				Update(rson(k),rson(pre),mid+1,r,pos);
		}
		return;
	}
	inline int Query(reg int x,reg int y,reg int pre1,reg int pre2,reg int l,reg int r,reg int k){
		if(l==r)
			return l;
		reg int sum=val(lson(x))+val(lson(y))-val(lson(pre1))-val(lson(pre2));
		if(k<=sum)
			return Query(lson(x),lson(y),lson(pre1),lson(pre2),l,mid,k);
		else
			return Query(rson(x),rson(y),rson(pre1),rson(pre2),mid+1,r,k-sum);
	}
	#undef mid
}

using namespace SegmentTree;

bool vis[MAXN];
int fa[MAXN][MAXLOG2N],dep[MAXN];
int son[MAXN];

inline void DFS(reg int ID,reg int father,reg int Root){
	vis[ID]=true;
	++son[Root];
	dep[ID]=dep[father]+1;
	fa[ID][0]=father;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	UnionFind::fa[ID]=father;
	Update(root[ID],root[father],1,S,a[ID]);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID,Root);
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int main(void){
	read();
	n=read(),m=read(),T=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	S=unique(b+1,b+n+1)-(b+1);
	for(reg int i=1;i<=n;++i)
		a[i]=GetID(a[i]);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	Init(n);
	Build(root[0],1,S);
	for(reg int i=1;i<=n;++i)
		if(!vis[i])
			DFS(i,0,i);
	reg int lastans=0;
	while(T--){
		static char opt;
		static int x,y,k;
		do
			opt=getchar();
		while(opt!='Q'&&opt!='L');
		switch(opt){
			case 'Q':{
				x=read()^lastans,y=read()^lastans,k=read()^lastans;
				reg int lca=LCA(x,y);
				reg int ans=Query(root[x],root[y],root[lca],root[fa[lca][0]],1,S,k);
				ans=b[ans];
				printf("%d\n",lastans=ans);
				break;
			}
			case 'L':{
				x=read()^lastans,y=read()^lastans;
				if(x==y)
					break;
				int u=find(x),v=find(y);
				if(son[u]<son[v])
					swap(u,v),swap(x,y);
				Add_Edge(x,y);
				Add_Edge(y,x);
				DFS(y,x,u);
				break;
			}
			default:break;
		}
	}
	return 0;
}