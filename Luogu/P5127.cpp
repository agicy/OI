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

const int MAXN=2e5+5;
const int mod=1e9+7;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int val[MAXN],pw2[MAXN];

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
	struct Node{
		int sand,sor,tag;
		#define sand(x) unit[(x)].sand
		#define sor(x) unit[(x)].sor
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sand(k)=sand(lson)&sand(rson);
		sor(k)=sor(lson)|sor(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			sor(k)=sand(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Xor(reg int k,reg int val){
		int a=sor(k),b=sand(k);
		sor(k)=(a&~val)|(val&~b);
		sand(k)=(b&~val)|(val&~a);
		tag(k)^=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			Xor(lson,tag(k)),Xor(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Xor(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sor(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)|query(rson,mid+1,r,L,R);
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

inline int query(int x,int y){
	reg int sor=0;
	reg int cnt=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		sor|=SegmentTree::query(1,1,n,dfn[top[y]],dfn[y]);
		cnt+=dfn[y]-dfn[top[y]]+1;
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	sor|=SegmentTree::query(1,1,n,dfn[x],dfn[y]);
	cnt+=dfn[y]-dfn[x]+1;
	return 1ll*sor*pw2[cnt-1]%mod;
}

int main(void){
	n=read(),m=read();
	pw2[0]=1;
	for(int i=1;i<=n;i++)
		pw2[i]=(pw2[i-1]<<1)%mod;
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	for(reg int i=1;i<=n;++i)
		val[i]=read();
	dfs1(1,0),dfs2(1,0,1);
	static int tmp[MAXN];
	for(reg int i=1;i<=n;++i)
		tmp[dfn[i]]=val[i];
	SegmentTree::build(1,1,n,tmp);
	while(m--){
		static int opt,a,b,c;
		opt=read();
		switch(opt){
			case 1:{
				a=read(),b=read();
				writeln(query(a,b));
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