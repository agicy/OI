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

const int MAXN=300000+5;
const int MAXLOG2N=30;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,q;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

struct SegmentTree{
	#define mid ( ( (l) + (r) )>>1)
	int cnt,root[MAXN];
	int lson[MAXN*MAXLOG2N],rson[MAXN*MAXLOG2N];
	ll val[MAXN*MAXLOG2N];
	inline void pushup(reg int ID){
		val[ID]=val[lson[ID]]+val[rson[ID]];
		return;
	}
	inline int Build(reg int l,reg int r){
		reg int root=++cnt;
		if(l==r)
			return root;
		lson[root]=Build(l,mid);
		rson[root]=Build(mid+1,r);
		return root;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg int pos,reg ll Val){
		reg int dir=++cnt;
		if(l==r){
			val[dir]=val[pre]+Val;
			return dir;
		}
		lson[dir]=lson[pre],rson[dir]=rson[pre];
		if(pos<=mid)
			lson[dir]=Update(lson[pre],l,mid,pos,Val);
		else
			rson[dir]=Update(rson[pre],mid+1,r,pos,Val);
		pushup(dir);
		return dir;
	}
	inline ll Query(reg int pre,reg int dir,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val[dir]-val[pre];
		reg ll res=0;
		if(L<=mid)
			res+=Query(lson[pre],lson[dir],l,mid,L,R);
		if(R>mid)
			res+=Query(rson[pre],rson[dir],mid+1,r,L,R);
		return res;
	}
	#undef mid
};

int Ti,dfn[MAXN];
ll dep[MAXN],size[MAXN];
SegmentTree T;

inline void DFS(reg int ID,reg int father){
	size[ID]=1;
	dfn[ID]=++Ti;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			size[ID]+=size[to[i]];
		}
	return;
}

inline void GetTree(reg int ID){
	T.root[dfn[ID]]=T.Update(T.root[dfn[ID]-1],1,n,dep[ID],size[ID]-1);
	for(reg int i=head[ID];i;i=Next[i])
		if(dep[to[i]]>dep[ID])
			GetTree(to[i]);
	return;
}

inline void Work(void){
	dep[1]=1;
	DFS(1,0);
	T.root[0]=T.Build(1,n);
	GetTree(1);
	while(q--){
		static ll p,K;
		p=read(),K=read();
		printf("%lld\n",T.Query(T.root[dfn[p]-1],T.root[dfn[p]+size[p]-1],1,n,dep[p]+1,dep[p]+K)+(ll)min(K,dep[p]-1)*(size[p]-1));
	}
	return;
}
