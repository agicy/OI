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

const int MAXN=5e4+5;
const int MAXQ=5e4+5;
const int p=998244353;

int n,Q,k;
int basep[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];

inline void dfs1(reg int u,reg int father){
	size[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs1(v,u);
		size[u]+=size[v];
		if(size[son[u]]<size[v])
			son[u]=v;
	}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int topf){
	dfn[u]=++tim;
	rnk[tim]=u;
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=son[u])
			dfs2(v,v);
	}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	inline int add(reg int a,reg int b,reg int mod){
		reg int sum=a+b;
		return sum>=mod?sum-mod:sum;
	}
	inline int mul(reg int a,reg int b,reg int mod){
		return 1ll*a*b%mod;
	}
	struct Node{
		int bas,sum,tag;
		#define bas(x) unit[(x)].bas
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		bas(k)=add(bas(lson),bas(rson),p);
		sum(k)=add(sum(lson),sum(rson),p);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			bas(k)=add(basep[dep[rnk[l]]],p-basep[dep[rnk[l]]-1],p);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int val){
		sum(k)=add(sum(k),mul(bas(k),val,p),p);
		tag(k)=add(tag(k),val,p);
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			add(lson,tag(k)),add(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			add(k,1);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R);
		if(R>mid)
			update(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k);
		reg int res=0;
		if(L<=mid)
			res=add(res,query(lson,l,mid,L,R),p);
		if(R>mid)
			res=add(res,query(rson,mid+1,r,L,R),p);
		return res;
	}
}

inline int add(reg int a,reg int b,reg int mod){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline int mul(reg int a,reg int b,reg int mod){
	return 1ll*a*b%mod;
}

inline void update(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		SegmentTree::update(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::update(1,1,n,dfn[x],dfn[y]);
	return;
}

inline int query(int x,int y){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		res=add(res,SegmentTree::query(1,1,n,dfn[top[x]],dfn[x]),p);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=add(res,SegmentTree::query(1,1,n,dfn[x],dfn[y]),p);
	return res;
}

struct querys{
	int id,pos,val;
	inline bool operator<(const querys& a)const{
		return pos<a.pos;
	}
	inline void Read(reg int i){
		id=i;
		pos=read(),val=read();
		return;
	}
};

querys q[MAXQ];
int ans[MAXQ];

int main(void){
	n=read(),Q=read(),k=read();
	for(reg int i=1;i<=n;++i)
		basep[i]=pow(i,k,p);
	for(reg int i=2;i<=n;++i){
		static int f;
		f=read();
		Add_Edge(f,i);
	}
	dfs1(1,0);
	dfs2(1,1);
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<=Q;++i)
		q[i].Read(i);
	sort(q+1,q+Q+1);
	reg int ptr=1;
	for(reg int i=1;i<=n;++i){
		update(1,i);
		while(q[ptr].pos<=i&&ptr<=Q){
			ans[q[ptr].id]=add(ans[q[ptr].id],query(1,q[ptr].val),p);
			++ptr;
		}
	}
	for(reg int i=1;i<=Q;++i)
		printf("%d\n",ans[i]);
	return 0;
}