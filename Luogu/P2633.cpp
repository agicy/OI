#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXLOG2N=17+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int v[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
vector<int> V;

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read(),V.push_back(v[i]);
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

const int MAXSIZE=MAXN<<5;

struct SegmentTree{
	#define mid ( ( (l) + (r) )>>1)
	int cnt,root[MAXN];
	int val[MAXSIZE],lson[MAXSIZE],rson[MAXSIZE];
	inline int Build(reg int l,reg int r){
		reg int root=++cnt;
		if(l==r)
			return root;
		lson[root]=Build(l,mid),rson[root]=Build(mid+1,r);
		return root;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg int Val){
		reg int dir=++cnt;
		val[dir]=val[pre]+1,lson[dir]=lson[pre],rson[dir]=rson[pre];
		if(l==r)
			return dir;
		if(Val<=mid)
			lson[dir]=Update(lson[pre],l,mid,Val);
		else
			rson[dir]=Update(rson[pre],mid+1,r,Val);
		return dir;
	}
	inline int Query(reg int x,reg int y,reg int z,reg int w,reg int l,reg int r,reg int k){
		if(l==r)
			return l;
		reg int sum=val[lson[x]]+val[lson[y]]-val[lson[z]]-val[lson[w]];
		if(k<=sum)
			return Query(lson[x],lson[y],lson[z],lson[w],l,mid,k);
		else
			return Query(rson[x],rson[y],rson[z],rson[w],mid+1,r,k-sum);
	}
	#undef mid
};

int DFN,dfn[MAXN];
int dep[MAXN],fa[MAXN][MAXLOG2N];
SegmentTree T;

inline void DFS(reg int ID,reg int father){
	dfn[ID]=++DFN;
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	T.root[dfn[ID]]=T.Update(T.root[dfn[father]],1,V.size(),v[ID]);
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID);
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

inline int Solve(reg int u,reg int v,reg int k){
	reg int lca=LCA(u,v);
	return V[T.Query(T.root[dfn[u]],T.root[dfn[v]],T.root[dfn[lca]],T.root[dfn[fa[lca][0]]],1,V.size(),k)-1];
}

inline void Work(void){
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		v[i]=lower_bound(V.begin(),V.end(),v[i])-V.begin()+1;
	T.root[0]=T.Build(1,n);
	DFS(1,0);
	reg int lastans=0;
	while(m--){
		static int u,v,k;
		u=read(),v=read(),k=read();
		u^=lastans;
		printf("%d\n",lastans=Solve(u,v,k));
	}
	return;
}
