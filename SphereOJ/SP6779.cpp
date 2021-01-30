#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n;
int x[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
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
	for(reg int i=head[u];i;i=Next[i]){
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
int tim,dfn[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node {
		int sum,lMax,rMax,Max,tag;
		bool cov;
		inline Node(reg int sum=0,reg int lMax=0,reg int rMax=0,reg int Max=0,reg int tag=0,reg bool cov=0):sum(sum),lMax(lMax),rMax(rMax),Max(Max),tag(tag),cov(cov){
			return;
		}
		#define sum(x) unit[(x)].sum
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
		#define cov(x) unit[(x)].cov
	};
	Node unit[MAXN<<2];
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		res.sum=a.sum+b.sum;
		res.lMax=max(a.lMax,a.sum+b.lMax);
		res.rMax=max(b.rMax,b.sum+a.rMax);
		res.Max=max(max(a.Max,b.Max),a.rMax+b.lMax);
		res.tag=res.cov=0;
		return res;
	}
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int val[]){
		if(l==r){
			sum(k)=val[l];
			lMax(k)=rMax(k)=Max(k)=max(sum(k),0);
			cov(k)=false;
			return;
		}
		build(lson,l,mid,val),build(rson,mid+1,r,val);
		pushup(k);
		return;
	}
	inline void cover(reg int k,reg int l,reg int r,reg int val){
		sum(k)=(r-l+1)*val;
		lMax(k)=rMax(k)=Max(k)=max(sum(k),0);
		cov(k)=true,tag(k)=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(cov(k)){
			cover(lson,l,mid,tag(k));
			cover(rson,mid+1,r,tag(k));
			cov(k)=false;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cover(k,l,r,val);
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
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
}

inline void update(int x,int y,reg int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		SegmentTree::update(1,1,n,dfn[top[y]],dfn[y],val);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::update(1,1,n,dfn[x],dfn[y],val);
	return;
}

inline SegmentTree::Node query(reg int x,reg int y){
	SegmentTree::Node l,r;
	while(top[x]!=top[y])
		if(dep[top[x]]<dep[top[y]]){
			r=SegmentTree::query(1,1,n,dfn[top[y]],dfn[y])+r;
			y=fa[top[y]];
		}
		else{
			l=SegmentTree::query(1,1,n,dfn[top[x]],dfn[x])+l;
			x=fa[top[x]];
		}
	if(dep[x]>dep[y])
		l=SegmentTree::query(1,1,n,dfn[y],dfn[x])+l;
	else
		r=SegmentTree::query(1,1,n,dfn[x],dfn[y])+r;
	swap(l.lMax,l.rMax);
	return l+r;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0),dfs2(1,0,1);
	static int val[MAXN];
	for(reg int i=1;i<=n;++i)
		val[dfn[i]]=x[i];
	SegmentTree::build(1,1,n,val);
	reg int q=read();
	while(q--){
		static int opt,a,b,c;
		opt=read();
		switch(opt){
			case 1:{
				a=read(),b=read();
				writeln(query(a,b).Max);
				break;
			}
			case 2:{
				a=read(),b=read(),c=read();
				update(a,b,c);
				break;
			}
		}
	}
	flush();
	return 0;
}