#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F3F3F3F3Fll
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

const int MAXN=100000+5;
const int MAXLOG2N=17+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,root;
ll w[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int size[MAXN],son[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[to[i]]>size[son[ID]])
				son[ID]=to[i];
		}
	return;
}

int DFN,dfn[MAXN],rank[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++DFN;
	rank[dfn[ID]]=ID;
	if(!son[ID])
		return;
	DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll Min,tag;
		inline Node(reg ll Min=0,reg ll tag=0):Min(Min),tag(tag){
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=Node(min(unit[lson].Min,unit[rson].Min),0);
		return;
	}
	inline void Change(reg int k,reg ll val){
		unit[k].Min=val;
		unit[k].tag=val;
		return;
	}
	inline void pushdown(reg int k){
		if(unit[k].tag){
			Change(lson,unit[k].tag);
			Change(rson,unit[k].tag);
			unit[k].tag=0;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg ll w[],reg int rank[]){
		if(l==r){
			unit[k]=Node(w[rank[l]],0);
			return;
		}
		Build(lson,l,mid,w,rank);
		Build(rson,mid+1,r,w,rank);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Change(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].Min;
		pushdown(k);
		ll res=INF;
		if(L<=mid)
			res=min(res,Query(lson,l,mid,L,R));
		if(R>mid)
			res=min(res,Query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline void Update(int u,int v,reg ll w){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		T.Update(1,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]][0];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	T.Update(1,1,n,dfn[u],dfn[v],w);
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

inline void Work(void){
	root=read();
	dep[1]=1;
	DFS1(1,0);
	DFS2(1,0,1);
	T.Build(1,1,n,w,rank);
	while(m--){
		static int opt,x,y;
		static ll k;
		opt=read();
		switch(opt){
			case 1:root=read();break;
			case 2:x=read(),y=read(),k=read();Update(x,y,k);break;
			case 3:x=read();
				if(x==root)
					printf("%lld\n",T.unit[1].Min);
				else
					if(LCA(x,root)==x){
						reg int c=dep[root]-dep[x]-1;
						reg int v=root;
						for(reg int i=0;i<MAXLOG2N;++i)
							if(c&(1<<i))
								v=fa[v][i];
						ll ans=min(T.Query(1,1,n,1,dfn[v]-1),T.Query(1,1,n,dfn[v]+size[v],n));
						printf("%lld\n",ans);
					}
					else
						printf("%lld\n",T.Query(1,1,n,dfn[x],dfn[x]+size[x]-1));
			break;
		}
	}
	return;
}
