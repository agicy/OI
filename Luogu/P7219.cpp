#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;

int n,m;
int a[MAXN];
int rt[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*80;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		ll Max,tag;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(void){
		return ++tot;
	}
	inline void pushup(reg int p){
		Max(p)=max(Max(lson(p)),Max(rson(p)));
		return;
	}
	inline void add(reg int p,reg ll Val){
		Max(p)+=Val,tag(p)+=Val;
		return;
	}
	inline void pushdown(reg int p){
		if(tag(p)){
			if(lson(p))
				add(lson(p),tag(p));
			if(rson(p))
				add(rson(p),tag(p));
			tag(p)=0;
		}
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int pos,ll Val){
		if(!p)
			p=New();
		Max(p)=max(Max(p),Val);
		if(l!=r){
			pushdown(p);
			if(pos<=mid)
				update(lson(p),l,mid,pos,Val);
			else
				update(rson(p),mid+1,r,pos,Val);
			pushup(p);
		}
		return;
	}
	inline void update(reg int p,reg int l,reg int r,reg int L,reg int R,reg ll Val){
		if(!p)
			return;
		if(L<=l&&r<=R){
			add(p,Val);
			return;
		}
		pushdown(p);
		if(L<=mid)
			update(lson(p),l,mid,L,R,Val);
		if(R>mid)
			update(rson(p),mid+1,r,L,R,Val);
		pushup(p);
		return;
	}
	inline ll query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return 0;
		if(L<=l&&r<=R)
			return Max(p);
		pushdown(p);
		if(L<=mid&&mid<R)
			return max(query(lson(p),l,mid,L,R),query(rson(p),mid+1,r,L,R));
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		pushdown(x),pushdown(y);
		reg int p=New();
		Max(p)=max(Max(x),Max(y));
		lson(p)=merge(lson(x),lson(y)),rson(p)=merge(rson(x),rson(y));
		return p;
	}
	#undef mid
}

using namespace SegmentTree;

inline void merge(reg int x,reg int y,reg int h){
	reg ll a=query(rt[x],0,n,0,h),b=query(rt[y],0,n,0,h);
	update(rt[x],0,n,h,n,b),update(rt[y],0,n,h,n,a);
	reg ll sum=query(rt[x],0,n,0,h-1)+query(rt[y],0,n,0,h-1);
	update(rt[x],0,n,h-1,sum);
	rt[y]=merge(rt[x],rt[y]);
	return;
}

struct star{
	int y,c;
	inline star(reg int y=0,reg int c=0):y(y),c(c){
		return;
	}
};

int lson[MAXN],rson[MAXN];
vector<star> V[MAXN];

inline void solve(reg int u){
	for(reg int i=0,size=V[u].size();i<size;++i)
		SegmentTree::update(rt[u],0,n,V[u][i].y,V[u][i].c);
	if(lson[u])
		solve(lson[u]),merge(lson[u],u,a[u]);
	if(rson[u])
		solve(rson[u]),merge(rson[u],u,a[u]);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i){
		while(top&&a[i]>=a[S[top]])
			lson[i]=S[top--];
		if(top)
			rson[S[top]]=i;
		S[++top]=i;
	}
	reg int Rt=S[1];
	m=read();
	reg ll sum=0;
	for(reg int i=1;i<=m;++i){
		static int x,y,c;
		x=read(),y=read(),c=read();
		V[x].push_back(star(y,c));
		sum+=c;
	}
	solve(Rt);
	printf("%lld\n",sum-query(rt[Rt],0,n,0,n));
	return 0;
}