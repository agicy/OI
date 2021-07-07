#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e3+5;
const int inf=0x3f3f3f3f;

int n,D;
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*30;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int Max;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
	};
	int rt,L,R;
	int tot;
	Node unit[MAXSIZE];
	vector<pair<int,int>> V;
	inline int getId(void){
		reg int p=++tot;
		lson(p)=rson(p)=0,Max(p)=-inf;
		return p;
	}
	inline void init(void){
		tot=rt=0;
		Max(0)=-inf;
		V.clear();
		L=-n*2,R=n*2;
		return;
	}
	inline void pushup(reg int p){
		Max(p)=max(Max(lson(p)),Max(rson(p)));
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=getId();
		if(l==r){
			Max(p)=val;
			return;
		}
		if(pos<=mid)
			update(lson(p),l,mid,pos,val);
		else
			update(rson(p),mid+1,r,pos,val);
		pushup(p);
		return;
	}
	inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return -inf;
		if(L<=l&&r<=R)
			return Max(p);
		if(L<=mid&&mid<R)
			return max(query(lson(p),l,mid,L,R),query(rson(p),mid+1,r,L,R));
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	inline void update(int pos,reg int val){
		int v=query(rt,L,R,pos,pos);
		V.push_back(make_pair(pos,v));
		if(val>v)
			update(rt,L,R,pos,val);
		return;
	}
	inline void undo(void){
		update(rt,L,R,V.back().first,V.back().second);
		V.pop_back();
		return;
	}
	inline int query(reg int pos){
		return query(rt,L,R,L,pos-1);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef Max
}

int dep[MAXN];
int Max[MAXN],cMax[MAXN],ccMax[MAXN];
int f[MAXN],g[MAXN],h[MAXN];

inline void dfs1(reg int u,reg int father){
	dep[u]=dep[father]+1;
	Max[u]=cMax[u]=ccMax[u]=0;
	f[u]=g[u]=h[u]=0;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			ccMax[u]=max(ccMax[u],Max[v]+1);
			if(ccMax[u]>cMax[u])
				swap(cMax[u],ccMax[u]);
			if(cMax[u]>Max[u])
				swap(Max[u],cMax[u]);
			h[u]=max(h[u],h[v]),g[u]=max(g[u],h[v]);
			if(g[u]>f[u])
				swap(f[u],g[u]);
		}
	}
	h[u]=max(h[u],Max[u]+cMax[u]);
	return;
}

inline int getLen(reg int u,reg int v){
	if(Max[v]+1==Max[u])
		return cMax[u]+ccMax[u];
	else if(Max[v]+1==cMax[u])
		return Max[u]+ccMax[u];
	else
		return Max[u]+cMax[u];
}

inline int getMax(reg int u,reg int v){
	if(h[v]==f[u])
		return g[u];
	else
		return f[u];
}

inline int getVal(reg int u,reg int v){
	if(Max[v]+1==Max[u])
		return cMax[u];
	else
		return Max[u];
}

int rt;
int ans=0;

inline void dfs2(reg int u,reg int father,reg int lim){
	if(dep[u]>lim)
		return;
	if(u!=rt&&h[u]<=D){
		if(dep[u]<=min(lim,D-SegmentTree::query(Max[u]+dep[u]-D)+dep[u]-Max[u]))
			++ans;
	}
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			if(getLen(u,v)>D||getMax(u,v)>D)
				continue;
			int val=D-SegmentTree::query(getVal(u,v)+dep[u]-D)+dep[u]-getVal(u,v);
			SegmentTree::update(dep[u]-getVal(u,v),dep[u]+getVal(u,v));
			dfs2(v,u,min(val,lim));
			SegmentTree::undo();
		}
	}
	return;
}

bool ed;

int main(void){
	n=read(),D=read();
	for(reg int i=2;i<=n;++i){
		static int f;
		f=read()+1;
		Add_Edge(f,i),Add_Edge(i,f);
	}
	dep[0]=-1;
	for(rt=1;rt<=n;++rt){
		dfs1(rt,0);
		SegmentTree::init();
		dfs2(rt,0,inf);
	}
	ans>>=1;
	dfs1(1,0);
	if(h[1]<=D)
		ans+=n;
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}