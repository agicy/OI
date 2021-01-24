#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<20];int wp1;const int wp2=1<<20;
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


const int MAXN=1e5+5;
const int MAXQ=2e5+5;

int n,q;
int col[MAXN];
int rt[MAXN+MAXQ*2];
map<int,int> M;

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
	const int MAXSIZE=MAXN*80;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=++tot;
		sum(p)+=val;
		if(l!=r){
			if(pos<=mid)
				update(lson(p),l,mid,pos,val);
			else
				update(rson(p),mid+1,r,pos,val);
		}
		return;
	}
	inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return 0;
		if(L<=l&&r<=R)
			return sum(p);
		if(L<=mid&&mid<R)
			return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
}

inline int query(int x,int y,reg int rt){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=SegmentTree::query(rt,1,n,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res+=SegmentTree::query(rt,1,n,dfn[x],dfn[y]);
	return res;
}

int main(void){
	n=read(),q=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i){
		static int c;
		c=read();
		if(!M[c]) M[c]=++tot;
		col[i]=M[c];
	}
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	dfs1(1,0),dfs2(1,0,1);
	for(reg int i=1;i<=n;++i)
		SegmentTree::update(rt[col[i]],1,n,dfn[i],1);
	while(q--){
		static char opt;
		static int i,j,x;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'C':{
				i=read(),x=read();
				if(!M[x]) M[x]=++tot;
				SegmentTree::update(rt[col[i]],1,n,dfn[i],-1);
				col[i]=M[x];
				SegmentTree::update(rt[col[i]],1,n,dfn[i],1);
				break;
			}
			case 'Q':{
				i=read(),j=read(),x=read();
				if(!M[x]) M[x]=++tot;
				writeln(query(i,j,rt[M[x]]));
				break;
			}
		}
	}
	flush();
	return 0;
}