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

const int MAXN=30000+5;
const int MAXM=100000+5;
const int MAXQ=40000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt=1,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Querys{
	int c,a,b;
	inline void Read(void){
		c=read();
		if(c==-1)
			return;
		a=read(),b=read();
		if(a>b)
			swap(a,b);
		return;
	}
};

int tot;
pair<int,int> P[MAXM];
Querys Q[MAXQ];
map<pair<int,int>,bool> M;

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		if(a>b)
			swap(a,b);
		P[i]=make_pair(a,b);
	}
	while(true){
		++tot;
		Q[tot].Read();
		if(Q[tot].c==-1){
			--tot;
			break;
		}
		else if(Q[tot].c==0)
			M[make_pair(Q[tot].a,Q[tot].b)]=true;
	}
	for(reg int i=1;i<=m;++i)
		if(!M[P[i]]){
			Add_Edge(P[i].first,P[i].second);
			Add_Edge(P[i].second,P[i].first);
		}
	return;
}

int fa[MAXN],dep[MAXN];
int size[MAXN],son[MAXN];
bool vis[MAXM<<1];
int val[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(!vis[i]&&!vis[i^1]&&!dep[to[i]]){
			vis[i]=true;
			val[to[i]]=1;
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[to[i]]>size[son[ID]])
				son[ID]=to[i];
		}
	return;
}

int DFN,dfn[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int topf){
	top[ID]=topf;
	dfn[ID]=++DFN;
	if(!son[ID])
		return;
	DFS2(son[ID],topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(vis[i]&&to[i]!=son[ID])
			DFS2(to[i],to[i]);
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum;
		bool tag0;
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].sum=unit[lson].sum+unit[rson].sum;
		unit[k].tag0=false;
		return;
	}
	inline void Set0(reg int k){
		unit[k].sum=0;
		unit[k].tag0=true;
		return;
	}
	inline void pushdown(reg int k){
		if(unit[k].tag0){
			Set0(lson);
			Set0(rson);
			unit[k].tag0=false;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			unit[k].sum=a[l];
			unit[k].tag0=false;
			return;
		}
		Build(lson,l,mid,a),Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void UpdateSet0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			Set0(k);
			return;
		}
		pushdown(k);
		if(L<=mid)
			UpdateSet0(lson,l,mid,L,R);
		if(R>mid)
			UpdateSet0(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		pushdown(k);
		reg int res=0;
		if(L<=mid)
			res+=Query(lson,l,mid,L,R);
		if(R>mid)
			res+=Query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline void Update(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		T.UpdateSet0(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		T.UpdateSet0(1,1,n,dfn[u]+1,dfn[v]);
	return;
}

inline int Query(int u,int v){
	reg int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		res+=T.Query(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		res+=T.Query(1,1,n,dfn[u]+1,dfn[v]);
	return res;
}

int ans[MAXQ];

inline void Work(void){
	DFS1(1,0);
	DFS2(1,1);
	static int temp[MAXN];
	for(reg int i=1;i<=n;++i)
		temp[dfn[i]]=val[i];
	T.Build(1,1,n,temp);
	for(reg int i=2;i<=cnt;i+=2)
		if(!vis[i]&&!vis[i^1])
			Update(to[i],to[i^1]);
	for(reg int i=tot;i>=1;--i)
		if(Q[i].c==0)
			Update(Q[i].a,Q[i].b),ans[i]=-1;
		else if(Q[i].c==1)
			ans[i]=Query(Q[i].a,Q[i].b);
	for(reg int i=1;i<=tot;++i)
		if(ans[i]!=-1)
			printf("%d\n",ans[i]);
	return;
}
