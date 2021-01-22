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

const int MAXN=8e4+5;
const int MAXQ=8e4+5;
const int MAXLOG2N=17+1;

int n,q;
int t[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int k[MAXQ],a[MAXQ],b[MAXQ];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int siz[MAXN],son[MAXN];
int tim,dfn[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	dfn[u]=++tim;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
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

namespace SegmentTree{
	const int MAXSIZE=MAXN*300;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	Node unit[MAXSIZE];
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=++tot;
		cnt(p)+=val;
		if(l!=r){
			if(pos<=mid)
				update(lson(p),l,mid,pos,val);
			else
				update(rson(p),mid+1,r,pos,val);
		}
		return;
	}
	#undef mid
}

int Max;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int rt[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,Max,pos,val);
		return;
	}
	bool vis[MAXN];
	int S[MAXN];
	int ptr[MAXN];
	inline int query(reg int p,reg int q,reg int pre,reg int pref,reg int k){
		reg int top=0;
		for(reg int i=p;i;i^=lowbit(i)){
			if(vis[i])
				continue;
			S[++top]=i;
			vis[i]=true;
		}
		for(reg int i=q;i;i^=lowbit(i)){
			if(vis[i])
				continue;
			S[++top]=i;
			vis[i]=true;
		}
		for(reg int i=pre;i;i^=lowbit(i)){
			if(vis[i])
				continue;
			S[++top]=i;
			vis[i]=true;
		}
		for(reg int i=pref;i;i^=lowbit(i)){
			if(vis[i])
				continue;
			S[++top]=i;
			vis[i]=true;
		}
		for(reg int i=1;i<=top;++i)
			ptr[S[i]]=rt[S[i]];
		reg int l=1,r=Max,mid;
		while(l<r){
			mid=(l+r)>>1;
			reg int sum=0;
			for(reg int i=p;i;i^=lowbit(i))
				sum+=SegmentTree::cnt(SegmentTree::lson(ptr[i]));
			for(reg int i=q;i;i^=lowbit(i))
				sum+=SegmentTree::cnt(SegmentTree::lson(ptr[i]));
			for(reg int i=pre;i;i^=lowbit(i))
				sum-=SegmentTree::cnt(SegmentTree::lson(ptr[i]));
			for(reg int i=pref;i;i^=lowbit(i))
				sum-=SegmentTree::cnt(SegmentTree::lson(ptr[i]));
			if(sum>=k){
				r=mid;
				for(reg int i=1;i<=top;++i)
					ptr[S[i]]=SegmentTree::lson(ptr[S[i]]);
			}
			else{
				k-=sum;
				l=mid+1;
				for(reg int i=1;i<=top;++i)
					ptr[S[i]]=SegmentTree::rson(ptr[S[i]]);
			}
		}
		for(reg int i=1;i<=top;++i)
			vis[S[i]]=false;
		return l;
	}
}

vector<int> V;

int main(void){
	n=read(),q=read();
	V.resize(n);
	for(reg int i=1;i<=n;++i)
		V[i-1]=t[i]=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	for(reg int i=1;i<=q;++i){
		k[i]=read(),a[i]=read(),b[i]=read();
		if(!k[i])
			V.push_back(b[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	Max=V.size();
	for(reg int i=1;i<=n;++i)
		t[i]=lower_bound(V.begin(),V.end(),t[i])-V.begin()+1;
	for(reg int i=1;i<=q;++i)
		if(!k[i])
			b[i]=lower_bound(V.begin(),V.end(),b[i])-V.begin()+1;
	dfs(1,0);
	BIT::Init(n);
	for(reg int i=1;i<=n;++i){
		BIT::update(dfn[i],t[i],1);
		BIT::update(dfn[i]+siz[i],t[i],-1);
	}
	for(reg int i=1;i<=q;++i)
		switch(k[i]){
			case 0:{
				reg int u=a[i],val=b[i];
				BIT::update(dfn[u],t[u],-1),BIT::update(dfn[u]+siz[u],t[u],1);
				t[u]=val;
				BIT::update(dfn[u],t[u],1),BIT::update(dfn[u]+siz[u],t[u],-1);
				break;
			}
			default:{
				reg int u=a[i],v=b[i],lca=LCA(u,v);
				k[i]=(dep[u]+dep[v]-dep[lca]-dep[fa[lca][0]])-k[i]+1;
				if(k[i]<=0)
					puts("invalid request!");
				else
					printf("%d\n",V[BIT::query(dfn[u],dfn[v],dfn[lca],dfn[fa[lca][0]],k[i])-1]);
				break;
			}
		}
	return 0;
}