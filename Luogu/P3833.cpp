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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read()+1,b=read()+1;
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	return;
}

int dep[MAXN],fa[MAXN];
int size[MAXN],son[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[to[i]]>size[son[ID]])
				son[ID]=to[i];
		}
	return;
}

int DFN,dfn[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++DFN;
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
		ll sum,tag;
		inline Node(reg ll sum=0,reg ll tag=0):sum(sum),tag(tag){
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=Node(unit[lson].sum+unit[rson].sum,0);
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg ll val){
		unit[k].sum+=(ll)(r-l+1)*val;
		unit[k].tag+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(unit[k].tag){
			Add(lson,l,mid,unit[k].tag);
			Add(rson,mid+1,r,unit[k].tag);
			unit[k].tag=0;
		}
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		pushdown(k,l,r);
		reg ll res=0;
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

inline void Update(int u,int v,reg ll val){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		T.Update(1,1,n,dfn[top[u]],dfn[u],val);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	T.Update(1,1,n,dfn[u],dfn[v],val);
	return;
}

inline ll Query(reg int u){
	return T.Query(1,1,n,dfn[u],dfn[u]+size[u]-1);
}

inline void Work(void){
	DFS1(1,0);
	DFS2(1,0,1);
	reg int Q=read();
	while(Q--){
		static char opt;
		do
			opt=getchar();
		while(opt!='A'&&opt!='Q');
		if(opt=='A'){
			static int u,v;
			static ll d;
			u=read()+1,v=read()+1,d=read();
			Update(u,v,d);
		}
		else if(opt=='Q'){
			static int u;
			u=read()+1;
			printf("%lld\n",Query(u));
		}
	}
	return;
}
