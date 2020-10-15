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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e5+5;

int n,q;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	dfn[u]=++tim;
	rnk[tim]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,tag;
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void set(reg int k,reg int val){
		cMax(Max(k),val),cMax(tag(k),val);
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			set(lson,tag(k));
			set(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			set(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return Max(k);
		pushdown(k);
		if(pos<=mid)
			return query(lson,l,mid,pos);
		else
			return query(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs(1,0);
	SegmentTree::update(1,1,n,dfn[1],dfn[1]+siz[1]-1,dfn[1]);
	while(q--){
		static char opt;
		static int num;
		do
			opt=getchar();
		while(opt!='C'&&opt!='Q');
		num=read();
		switch(opt){
			case 'C':{
				SegmentTree::update(1,1,n,dfn[num],dfn[num]+siz[num]-1,dfn[num]);
				break;
			}
			case 'Q':{
				reg int tim=SegmentTree::query(1,1,n,dfn[num]);
				printf("%d\n",rnk[tim]);
				break;
			}
		}
	}
	return 0;
}