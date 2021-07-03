#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline uint64_t read_uint64(void){
	reg char ch=getchar();
	reg uint64_t res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg uint64_t x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n,q,k;
int opt[MAXN];
uint64_t val[MAXN];
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int top[MAXN];
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	rnk[dfn[u]=++tim]=u;
	if(son[u])
		dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

struct Data{
	uint64_t lr0,lr1,rl0,rl1;
};

inline Data operator+(const Data& a,const Data& b){
	Data res;
	res.lr0=(a.lr0&b.lr1)|((~a.lr0)&b.lr0);
	res.lr1=(a.lr1&b.lr1)|((~a.lr1)&b.lr0);
	res.rl0=(b.rl0&a.rl1)|((~b.rl0)&a.rl0);
	res.rl1=(b.rl1&a.rl1)|((~b.rl1)&a.rl0);
	return res;
}

inline uint64_t calc(reg uint64_t x,reg int u){
	switch(opt[u]){
		case 1:return x&val[u];
		case 2:return x|val[u];
		case 3:return x^val[u];
		default:assert(false);
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		Data dat;
		#define dat(x) unit[(x)].dat
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		dat(k)=dat(lson)+dat(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			dat(k).lr0=dat(k).rl0=calc(0,rnk[l]);
			dat(k).lr1=dat(k).rl1=calc(-1,rnk[l]);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r){
			dat(k).lr0=dat(k).rl0=calc(0,rnk[l]);
			dat(k).lr1=dat(k).rl1=calc(-1,rnk[l]);
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos);
		else
			update(rson,mid+1,r,pos);
		pushup(k);
		return;
	}
	inline Data query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return dat(k);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
}

inline Data query(reg int x,reg int y){
	reg int cntl=0,cntr=0;
	static Data lef[MAXN],rig[MAXN];
	while(top[x]!=top[y])
		if(dep[top[x]]>=dep[top[y]])
			lef[++cntl]=SegmentTree::query(1,1,n,dfn[top[x]],dfn[x]),x=fa[top[x]];
		else
			rig[++cntr]=SegmentTree::query(1,1,n,dfn[top[y]],dfn[y]),y=fa[top[y]];
	if(dep[x]<dep[y])
		rig[++cntr]=SegmentTree::query(1,1,n,dfn[x],dfn[y]);
	else
		lef[++cntl]=SegmentTree::query(1,1,n,dfn[y],dfn[x]);
	Data res;
	for(reg int i=1;i<=cntl;++i)
		swap(lef[i].lr0,lef[i].rl0),swap(lef[i].lr1,lef[i].rl1);
	if(cntl){
		res=lef[1];
		for(reg int i=2;i<=cntl;++i)
			res=res+lef[i];
		for(reg int i=cntr;i>=1;--i)
			res=res+rig[i];
	}
	else{
		res=rig[cntr];
		for(reg int i=cntr-1;i>=1;--i)
			res=res+rig[i];
	}
	return res;
}

bool ed;

int main(void){
	n=read_uint64(),q=read_uint64(),k=read_uint64();
	for(reg int i=1;i<=n;++i)
		opt[i]=read_uint64(),val[i]=read_uint64();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read_uint64(),y=read_uint64();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	dfs1(1,0),dfs2(1,0,1);
	SegmentTree::build(1,1,n);
	while(q--){
		static int Q,x,y;
		static uint64_t z;
		Q=read_uint64(),x=read_uint64(),y=read_uint64(),z=read_uint64();
		switch(Q){
			case 1:{
				Data res=query(x,y);
				reg uint64_t ans=0;
				for(reg int i=k-1;i>=0;--i){
					reg uint64_t tmp0=(res.lr0>>i)&1ull;
					reg uint64_t tmp1=(res.lr1>>i)&1ull;
					if(tmp0>=tmp1||(1ull<<i)>z)
						ans|=tmp0<<i;
					else
						ans|=tmp1<<i,z-=(1ull<<i);
				}
				writeln(ans);
				break;
			}
			case 2:{
				opt[x]=y,val[x]=z;
				SegmentTree::update(1,1,n,dfn[x]);
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}