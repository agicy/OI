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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e4+5;

int n;
int u[MAXN],v[MAXN],w[MAXN];
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
	son[u]=0;
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

int tim,dfn[MAXN];
int top[MAXN];

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
		int Max;
		#define Max(x) unit[(x)].Max
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int val[]){
		if(l==r){
			Max(k)=val[l];
			return;
		}
		build(lson,l,mid,val),build(rson,mid+1,r,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Max(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		if(L<=mid&&mid<R)
			return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline int query(reg int x,reg int y){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res=max(res,SegmentTree::query(1,1,n,dfn[top[y]],dfn[y]));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	if(dfn[x]<dfn[y])
		res=max(res,SegmentTree::query(1,1,n,dfn[x]+1,dfn[y]));
	return res;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		cnt=0,fill(head+1,head+n+1,0);
		tim=0;
		for(reg int i=1;i<n;++i){
			u[i]=read(),v[i]=read(),w[i]=read();
			Add_Edge(u[i],v[i]),Add_Edge(v[i],u[i]);
		}
		dfs1(1,0),dfs2(1,0,1);
		static int val[MAXN];
		for(reg int i=1;i<n;++i){
			reg int son=dep[u[i]]>dep[v[i]]?u[i]:v[i];
			val[dfn[son]]=w[i];
		}
		SegmentTree::build(1,1,n,val);
		reg bool flag=true;
		while(flag){
			static char opt;
			static int a,b;
			do
				opt=getchar();
			while(!isalpha(opt));
			switch(opt){
				case 'Q':{
					a=read(),b=read();
					writeln(query(a,b));
					break;
				}
				case 'C':{
					a=read(),b=read();
					reg int son=dep[u[a]]>dep[v[a]]?u[a]:v[a];
					SegmentTree::update(1,1,n,dfn[son],b);
					break;
				}
				case 'D':{
					flag=false;
					break;
				}
			}
		}
	}
	flush();
	return 0;
}