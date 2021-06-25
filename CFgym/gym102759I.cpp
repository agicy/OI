#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

int n;
vector<int> G[MAXN];

int fa[MAXN][MAXLOG2N],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;(1<<i)<=dep[u];++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:G[u])
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	return;
}

int top[MAXN];
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	rnk[dfn[u]=++tim]=u;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(int v:G[u])
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,tag;
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg ll val){
		sum(k)+=(r-l+1)*val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			add(lson,l,mid,tag(k));
			add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	inline int query(reg int k,reg int l,reg int r,reg ll res){
		if(l==r)
			return l;
		pushdown(k,l,r);
		if(res<=sum(lson))
			return query(lson,l,mid,res);
		else
			return query(rson,mid+1,r,res-sum(lson));
	}
	#undef lson
	#undef rson
	#undef mid
	#undef sum
	#undef tag
}

inline void update(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		SegmentTree::update(1,1,n,dfn[top[y]],dfn[y],1);
		y=fa[top[y]][0];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::update(1,1,n,dfn[x],dfn[y],1);
	return;
}

inline void update(reg int x){
	SegmentTree::update(1,1,n,dfn[x],dfn[x]+siz[x]-1,1);
	return;
}

inline int query(void){
	reg ll S=SegmentTree::unit[1].sum;
	reg int tmp=rnk[SegmentTree::query(1,1,n,(S+1)>>1)];
	for(reg int i=MAXLOG2N-1;i>=0;--i){
		reg int p=fa[tmp][i];
		if(p&&SegmentTree::query(1,1,n,dfn[p],dfn[p]+siz[p]-1)<=(S>>1))
			tmp=p;
	}
	if(SegmentTree::query(1,1,n,dfn[tmp],dfn[tmp]+siz[tmp]-1)>(S>>1))
		return tmp;
	else
		return fa[tmp][0];
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	dfs1(1,0),dfs2(1,0,1);
	reg int q=read();
	while(q--){
		switch(read()){
			case 1:{
				update(read());
				break;
			}
			case 2:{
				update(read(),read());
				break;
			}
		}
		writeln(query());
	}
	flush();
	return 0;
}