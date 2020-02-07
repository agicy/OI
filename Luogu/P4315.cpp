#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int u[MAXN],v[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int w;
		u[i]=read(),v[i]=read(),w=read();
		Add_Edge(u[i],v[i],w);
		Add_Edge(v[i],u[i],w);
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
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]!=father){
			val[to[i]]=w[i];
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[to[i]]>size[son[ID]])
				son[ID]=to[i];
		}
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
		int Max,tagAdd,tagCover;
		inline Node(reg int Max=0,reg int tagAdd=0,reg int tagCover=-1):Max(Max),tagAdd(tagAdd),tagCover(tagCover){
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=Node(max(unit[lson].Max,unit[rson].Max),0,-1);
		return;
	}
	inline void Add(reg int k,reg int val){
		unit[k].Max+=val;
		unit[k].tagAdd+=val;
		return;
	}
	inline void Cover(reg int k,reg int val){
		unit[k].Max=val;
		unit[k].tagCover=val;
        unit[k].tagAdd=0;
		return;
	}
	inline void pushdown(reg int k){
		if(unit[k].tagCover!=-1){
            Cover(lson,unit[k].tagCover);
            Cover(rson,unit[k].tagCover);
            unit[k].tagCover=-1;
		}
		if(unit[k].tagAdd){
            Add(lson,unit[k].tagAdd);
            Add(rson,unit[k].tagAdd);
            unit[k].tagAdd=0;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg int a[],reg int rank[]){
		if(l==r){
			unit[k]=Node(a[rank[l]],0,-1);
			return;
		}
		Build(lson,l,mid,a,rank);
		Build(rson,mid+1,r,a,rank);
		pushup(k);
		return;
	}
	inline void UpdateCover(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(l>r||L>R||R<l||r<L)
			return;
		if(L<=l&&r<=R){
			Cover(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			UpdateCover(lson,l,mid,L,R,val);
		if(R>mid)
			UpdateCover(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline void UpdateAdd(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(l>r||L>R||R<l||r<L)
			return;
		if(L<=l&&r<=R){
			Add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			UpdateAdd(lson,l,mid,L,R,val);
		if(R>mid)
			UpdateAdd(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(l>r||L>R||R<l||r<L)
			return -1;
		if(L<=l&&r<=R)
			return unit[k].Max;
		pushdown(k);
		int res=-1;
		if(L<=mid)
			res=max(res,Query(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,Query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline void Cover(int u,int v,reg int w){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		T.UpdateCover(1,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		T.UpdateCover(1,1,n,dfn[u]+1,dfn[v],w);
	return;
}

inline void Add(int u,int v,reg int w){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		T.UpdateAdd(1,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		T.UpdateAdd(1,1,n,dfn[u]+1,dfn[v],w);
	return;
}

inline int Max(int u,int v){
	int Max=-1;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		Max=max(Max,T.Query(1,1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		Max=max(Max,T.Query(1,1,n,dfn[u]+1,dfn[v]));
	return Max;
}

inline void Work(void){
	DFS1(1,0);
	DFS2(1,0,1);
	T.Build(1,1,n,val,rank);
	while(true){
		static string str;
		cin>>str;
		if(str=="Change"){
			static int k,w;
			k=read(),w=read();
			reg int son=dep[u[k]]<dep[v[k]]?v[k]:u[k];
			T.UpdateCover(1,1,n,dfn[son],dfn[son],w);
		}
		else if(str=="Cover"){
			static int u,v,w;
			u=read(),v=read(),w=read();
			Cover(u,v,w);
		}
		else if(str=="Add"){
			static int u,v,w;
			u=read(),v=read(),w=read();
			Add(u,v,w);
		}
		else if(str=="Max"){
			static int u,v;
			u=read(),v=read();
			reg int ans=Max(u,v);
			printf("%d\n",ans);
		}
		else if(str=="Stop")
			break;
	}
	return;
}
