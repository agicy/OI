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

const int MAXN=100006+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int u[MAXN],v[MAXN],W[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct UnionFind{
	int ID[MAXN];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

int end;
UnionFind U;

inline void Read(void){
	n=read(),m=read();
	U.Init(n);
	for(reg int i=1;i<=n;++i){
		u[i]=read(),v[i]=read(),W[i]=read();
		if(!U.search(u[i],v[i])){
			U.merge(u[i],v[i]);
			Add_Edge(u[i],v[i],W[i]);
			Add_Edge(v[i],u[i],W[i]);
		}
		else
			end=i;
	}
	return;
}

int fa[MAXN],dep[MAXN];
int size[MAXN],son[MAXN];
int val[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			val[to[i]]=w[i];
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
		int sum;
		inline Node(reg int sum=0):sum(sum){
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=Node(unit[lson].sum+unit[rson].sum);
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg int a[],reg int rank[]){
		if(l==r){
			unit[k]=Node(a[rank[l]]);
			return;
		}
		Build(lson,l,mid,a,rank);
		Build(rson,mid+1,r,a,rank);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			unit[k].sum=val;
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,val);
		else
			Update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
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

inline int Query(int x,int y){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		res+=T.Query(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	if(x!=y)
		res+=T.Query(1,1,n,dfn[x]+1,dfn[y]);
	return res;
}

inline void Work(void){
	DFS1(1,0);
	DFS2(1,0,1);
	T.Build(1,1,n,val,rank);
	while(m--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		if(opt==1){
			if(x!=end){
				reg int son=dep[u[x]]<dep[v[x]]?v[x]:u[x];
				W[x]=y;
				T.Update(1,1,n,dfn[son],y);
			}
			else
				W[end]=y;
		}
		else if(opt==2){
			int ans=Query(x,y);
			int ans1=Query(x,u[end])+W[end]+Query(v[end],y);
			int ans2=Query(x,v[end])+W[end]+Query(u[end],y);
			printf("%d\n",min(ans,min(ans1,ans2)));
		}
	}
	return;
}
