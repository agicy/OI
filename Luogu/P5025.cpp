#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=500000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int tot;
ll x[MAXN],r[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),r[i]=read();
	return;
}

struct Graph{
	int cnt,head[MAXN<<2],to[MAXN*20],Next[MAXN*20];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
};

Graph G1,G2;

struct Node{
	int l,r;
	inline Node(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
};

Node a[MAXN<<2];
int L[MAXN<<2],R[MAXN<<2];
bool vis[MAXN<<2];
int tim,dfn[MAXN<<2],low[MAXN<<2];
int top,S[MAXN<<2];
int Tarjan_cnt,color[MAXN<<2];

inline void Tarjan(reg int ID,Graph& G){
	vis[ID]=true;
	dfn[ID]=low[ID]=++tim;
	S[++top]=ID;
	for(reg int i=G.head[ID];i;i=G.Next[i])
		if(!dfn[G.to[i]]){
			Tarjan(G.to[i],G);
			low[ID]=min(low[ID],low[G.to[i]]);
		}
		else if(vis[G.to[i]])
			low[ID]=min(low[ID],dfn[G.to[i]]);
	if(dfn[ID]==low[ID]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=S[top--];
			vis[To]=false;
			color[To]=Tarjan_cnt;
			L[Tarjan_cnt]=min(L[Tarjan_cnt],a[To].l);
			R[Tarjan_cnt]=max(R[Tarjan_cnt],a[To].r);
		}while(To!=ID);
	}
	return;
}

int id[MAXN<<2];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	inline void Build(int k,reg int l,reg int r){
		a[k]=Node(l,r);
		tot=max(tot,k);
		if(l==r){
			id[l]=k;
			return;
		}
		Build(lson,l,mid),Build(rson,mid+1,r);
		G1.Add_Edge(k,lson),G1.Add_Edge(k,rson);
		return;
	}
	inline void Add_Edge(reg int k,reg int l,reg int r,reg int L,reg int R,reg int p){
		if(L<=l&&r<=R){
			if(p==k)
				return;
			G1.Add_Edge(p,k);
			return;
		}
		if(L<=mid)
			Add_Edge(lson,l,mid,L,R,p);
		if(R>mid)
			Add_Edge(rson,mid+1,r,L,R,p);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void DFS(reg int ID,const Graph& G){
	vis[ID]=true;
	for(reg int i=G.head[ID];i;i=G.Next[i]){
		if(!vis[G.to[i]])
			DFS(G.to[i],G);
		L[ID]=min(L[ID],L[G.to[i]]);
		R[ID]=max(R[ID],R[G.to[i]]);
	}
	return;
}

inline ll Query(reg int i){
	reg int ID=color[id[i]];
	return R[ID]-L[ID]+1;
}

inline void Work(void){
	memset(L,0X3F,sizeof(L));
	x[n+1]=INF;
	SegmentTree::Build(1,1,n);
	for(reg int i=1;i<=n;++i){
		if(!r[i])
			continue;
		reg int L=lower_bound(x+1,x+1+n,x[i]-r[i])-x;
		reg int R=upper_bound(x+1,x+1+n,x[i]+r[i])-x-1;
		SegmentTree::Add_Edge(1,1,n,L,R,id[i]);
		a[id[i]]=Node(L,R);
	}
	Tarjan(1,G1);
	for(reg int i=1;i<=tot;++i)
		for(reg int j=G1.head[i];j;j=G1.Next[j])
			if(color[i]!=color[G1.to[j]])
				G2.Add_Edge(color[i],color[G1.to[j]]);
	memset(vis,false,sizeof(vis));
	for(reg int i=1;i<=Tarjan_cnt;++i)
		if(!vis[i])
			DFS(i,G2);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans=(ans+Query(i)*i%MOD)%MOD;
	printf("%d\n",ans);
	return;
}