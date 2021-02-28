#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline void swap(reg int &a,reg int &b){
	a^=b,b^=a,a^=b;
	return;
}

const int MAXN=2e5+5;

int n,q;
int L,R,len;
int rt,las;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];

inline void getDis(reg int u,reg int father){
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			getDis(v,u);
	}
	return;
}

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
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	rnk[dfn[u]=++tim]=u;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u]){
			dfs2(v,u,v);
		}
	}
	return;
}

int f[MAXN],g[MAXN];

inline void Init(reg int u,reg int father){
	f[u]=0;
	g[u]=(dfn[u]<=dfn[L]&&dfn[L]<=dfn[u]+siz[u]-1?dep[R]:dep[L])+dep[u]-(len&1);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			Init(v,u);
			f[u]=max(f[u],f[v]+1);
		}
	}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) +(r) ) >> 1 )
	struct Matrix{
		int unit[2][2];
		inline void swap0(void){
			swap(unit[0][0],unit[1][0]),swap(unit[0][1],unit[1][1]);
			return;
		}
		inline void swap1(void){
			swap(unit[0][0],unit[0][1]),swap(unit[1][0],unit[1][1]);
			return;
		}
		inline int* operator[](reg int i){
			return unit[i];
		}
	};
	inline Matrix operator+(const Matrix &a,const Matrix &b){
		Matrix res;
		res[0][0]=a.unit[0][0]^b.unit[0][0];
		res[0][1]=a.unit[0][1]^b.unit[0][1];
		res[1][0]=a.unit[1][0]^b.unit[1][0];
		res[1][1]=a.unit[1][1]^b.unit[1][1];
		return res;
	}
	struct Node{
		Matrix M;
		bool tS0,tS1;
		#define M(x) unit[(x)].M
		#define tS0(x) unit[(x)].tS0
		#define tS1(x) unit[(x)].tS1
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		M(k)=M(lson)+M(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int f[],reg int g[],reg int rnk[]){
		if(l==r){
			reg int u=rnk[l];
			M(k).unit[0][0]=f[u],M(k).unit[0][1]=0;
			M(k).unit[1][0]=g[u],M(k).unit[1][1]=0;
			return;
		}
		build(lson,l,mid,f,g,rnk),build(rson,mid+1,r,f,g,rnk);
		pushup(k);
		return;
	}
	inline void swap0(reg int k){
		M(k).swap0();
		tS0(k)=!tS0(k);
		return;
	}
	inline void swap1(reg int k){
		M(k).swap1();
		tS1(k)=!tS1(k);
		return;
	}
	inline void pushdown(reg int k){
		if(tS0(k)){
			swap0(lson),swap0(rson);
			tS0(k)=false;
		}
		if(tS1(k)){
			swap1(lson),swap1(rson);
			tS1(k)=false;
		}
		return;
	}
	inline void update0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			swap0(k);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update0(lson,l,mid,L,R);
		if(R>mid)
			update0(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline void update1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			swap1(k);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update1(lson,l,mid,L,R);
		if(R>mid)
			update1(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void ChangeRt(reg int x){
	int u=las,v=x;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]])
			swap(u,v);
		SegmentTree::update0(1,1,n,dfn[top[v]],dfn[v]);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		SegmentTree::update0(1,1,n,dfn[son[u]],dfn[v]);
	las=x;
	return;
}

inline void update(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		SegmentTree::update1(1,1,n,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::update1(1,1,n,dfn[x],dfn[y]);
	return;
}

inline void update(reg int u){
	if(u==las)
		SegmentTree::update1(1,1,n,1,n);
	else if(dfn[u]<=dfn[las]&&dfn[las]<=dfn[u]+siz[u]-1){
		reg int x=son[u];
		if(!(dfn[x]<=dfn[las]&&dfn[las]<=dfn[x]+siz[x]-1)){
			x=las;
			while(fa[top[x]]!=u)
				x=fa[top[x]];
			x=top[x];
		}
		if(1<=dfn[x]-1)
			SegmentTree::update1(1,1,n,1,dfn[x]-1);
		if(dfn[x]+siz[x]<=n)
			SegmentTree::update1(1,1,n,dfn[x]+siz[x],n);
	}
	else
		SegmentTree::update1(1,1,n,dfn[u],dfn[u]+siz[u]-1);
	return;
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	getDis(1,0);
	L=1;
	for(reg int i=2;i<=n;++i)
		if(dep[i]>dep[L])
			L=i;
	getDis(L,0);
	R=1;
	for(reg int i=2;i<=n;++i)
		if(dep[i]>dep[R])
			R=i;
	len=dep[R]-1;
	if(len&1){
		reg int x=R,y;
		for(reg int i=0;i<(len>>1);++i)
			x=fa[x];
		y=fa[x];
		rt=++n;
		for(reg int i=head[x];i;i=Next[i])
			if(to[i]==y){
				to[i]=rt;
				break;
			}
		for(reg int i=head[y];i;i=Next[i])
			if(to[i]==x){
				to[i]=rt;
				break;
			}
		Add_Edge(rt,x),Add_Edge(rt,y);
	}
	else{
		rt=R;
		for(reg int i=0;i<(len>>1);++i)
			rt=fa[rt];
	}
	dep[0]=-1;
	dfs1(rt,0),dfs2(rt,0,rt),Init(rt,0);
	if(len&1)
		f[rt]=g[rt]=0;
	las=rt;
	SegmentTree::build(1,1,n,f,g,rnk);
	ChangeRt(1);
	while(q--){
		static int opt,u,v,x;
		opt=read();
		switch(opt){
			case 1:{
				u=read(),v=read(),x=read();
				update(u,v);
				ChangeRt(x);
				break;
			}
			case 2:{
				u=read(),x=read();
				update(u);
				ChangeRt(x);
				break;
			}
		}
		writeln(SegmentTree::M(1).unit[0][0]);
	}
	flush();
	return 0;
}