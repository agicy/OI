#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F3F3F3F3Fll
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

const int MAXN=20000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int u[MAXN],v[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

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
		u[i]=read()+1,v[i]=read()+1,w=read();
		Add_Edge(u[i],v[i],w);
		Add_Edge(v[i],u[i],w);
	}
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,Max,Min,tag;
		inline Node(reg ll sum=0,reg ll Max=0,reg ll Min=0,reg ll tag=1):sum(sum),Max(Max),Min(Min),tag(tag){
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=Node(unit[lson].sum+unit[rson].sum,max(unit[lson].Max,unit[rson].Max),min(unit[lson].Min,unit[rson].Min),1);
		return;
	}
	inline void Mul(reg int k,reg ll val){
		unit[k].sum*=val;
		reg ll tMax=unit[k].Max;
		reg ll tMin=unit[k].Min;
		unit[k].Max=-tMin;
		unit[k].Min=-tMax;
		unit[k].tag*=val;
		return;
	}
	inline void pushdown(reg int k){
		if(unit[k].tag!=1){
			Mul(lson,unit[k].tag);
			Mul(rson,unit[k].tag);
			unit[k].tag=1;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			unit[k]=Node(a[l],a[l],a[l],1);
			return;
		}
		Build(lson,l,mid,a);
		Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void UpdateSet(reg int k,reg int l,reg int r,reg int pos,reg ll val){
		if(l==r){
			unit[k]=Node(val,val,val,1);
			return;
		}
		pushdown(k);
		if(pos<=mid)
			UpdateSet(lson,l,mid,pos,val);
		else
			UpdateSet(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline void UpdateMul(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Mul(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			UpdateMul(lson,l,mid,L,R,val);
		if(R>mid)
			UpdateMul(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll QuerySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		pushdown(k);
		reg ll res=0;
		if(L<=mid)
			res+=QuerySum(lson,l,mid,L,R);
		if(R>mid)
			res+=QuerySum(rson,mid+1,r,L,R);
		return res;
	}
	inline ll QueryMax(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].Max;
		pushdown(k);
		ll res=-INF;
		if(L<=mid)
			res=max(res,QueryMax(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,QueryMax(rson,mid+1,r,L,R));
		return res;
	}
	inline ll QueryMin(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].Min;
		pushdown(k);
		ll res=INF;
		if(L<=mid)
			res=min(res,QueryMin(lson,l,mid,L,R));
		if(R>mid)
			res=min(res,QueryMin(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

int fa[MAXN],dep[MAXN];
int size[MAXN],son[MAXN];
ll a[MAXN];
ll val[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			a[to[i]]=w[i];
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
	val[dfn[ID]]=a[ID];
	if(!son[ID])
		return;
	DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

SegmentTree T;

inline void Update(reg int u,reg ll val){
	T.UpdateSet(1,1,n,dfn[u],val);
	return;
}

inline void Update(int u,int v,reg ll val){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		T.UpdateMul(1,1,n,dfn[top[u]],dfn[u],val);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		T.UpdateMul(1,1,n,dfn[u]+1,dfn[v],val);
	return;
}

inline ll QuerySum(int u,int v){
	reg ll res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		res+=T.QuerySum(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		res+=T.QuerySum(1,1,n,dfn[u]+1,dfn[v]);
	return res;
}

inline ll QueryMax(int u,int v){
	ll res=-INF;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		res=max(res,T.QueryMax(1,1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		res=max(res,T.QueryMax(1,1,n,dfn[u]+1,dfn[v]));
	return res;
}

inline ll QueryMin(int u,int v){
	ll res=INF;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		res=min(res,T.QueryMin(1,1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		res=min(res,T.QueryMin(1,1,n,dfn[u]+1,dfn[v]));
	return res;
}

inline void Work(void){
	DFS1(1,0);
	DFS2(1,0,1);
	T.Build(1,1,n,val);
	reg int Q=read();
	while(Q--){
		static char opt;
		do
			opt=getchar();
		while(opt!='C'&&opt!='N'&&opt!='S'&&opt!='M');
		if(opt=='C'){
			static int x;
			static ll w;
			x=read(),w=read();
			reg int son=dep[u[x]]>dep[v[x]]?u[x]:v[x];
			Update(son,w);
		}
		else if(opt=='N'){
			static int u,v;
			u=read()+1,v=read()+1;
			Update(u,v,-1);
		}
		else if(opt=='S'){
			static int u,v;
			u=read()+1,v=read()+1;
			reg ll ans=QuerySum(u,v);
			printf("%lld\n",ans);
		}
		else if(opt=='M'){
			static char opt;
			do
				opt=getchar();
			while(opt!='A'&&opt!='I');
			if(opt=='A'){
				static int u,v;
				u=read()+1,v=read()+1;
				reg ll ans=QueryMax(u,v);
				printf("%lld\n",ans);
			}
			else if(opt=='I'){
				static int u,v;
				u=read()+1,v=read()+1;
				reg ll ans=QueryMin(u,v);
				printf("%lld\n",ans);
			}
		}
	}
	return;
}
