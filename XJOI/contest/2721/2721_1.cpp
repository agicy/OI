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
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll dMax,dMin,lefD,rigD,Max,tAdd;
		#define dMax(x) unit[(x)].dMax
		#define dMin(x) unit[(x)].dMin
		#define lefD(x) unit[(x)].lefD
		#define rigD(x) unit[(x)].rigD
		#define Max(x) unit[(x)].Max
		#define tAdd(x) unit[(x)].tAdd
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k){
		dMax(k)=max(dMax(lson),dMax(rson)),dMin(k)=max(dMin(lson),dMin(rson));
		lefD(k)=max(max(lefD(lson),lefD(rson)),dMax(lson)+dMin(rson)),rigD(k)=max(max(rigD(lson),rigD(rson)),dMin(lson)+dMax(rson));
		Max(k)=max(max(Max(lson),Max(rson)),max(lefD(lson)+dMax(rson),dMax(lson)+rigD(rson)));
		return;
	}
	inline void add(reg int k,reg ll val){
		dMax(k)+=val,dMin(k)-=val*2;
		lefD(k)-=val,rigD(k)-=val;
		tAdd(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tAdd(k)){
			add(lson,tAdd(k)),add(rson,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			dMax(k)=dMin(k)=lefD(k)=rigD(k)=Max(k)=0;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			add(k,val);
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
	#undef lson
	#undef rson
	#undef mid
}

int n,q;
ll c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

ll dis[MAXN];
int tim,lef[MAXN],rig[MAXN],rnk[MAXN<<1];

inline void dfs(reg int u){
	rnk[lef[u]=++tim]=u;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		dfs(v);
		rnk[++tim]=u;
	}
	rig[u]=tim;
	return;
}

bool ed;

int main(void){
	n=read(),q=read();
	for(reg int i=2;i<=n;++i)
		Add_Edge(read(),i);
	dfs(1);
	SegmentTree::build(1,1,tim);
	while(q--){
		static int d;
		static ll e;
		d=read(),e=readll();
		SegmentTree::update(1,1,tim,lef[d],rig[d],e-c[d]);
		c[d]=e;
		writeln(SegmentTree::Max(1));
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}