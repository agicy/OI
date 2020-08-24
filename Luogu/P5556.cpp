#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,q;

struct Graph{
	struct node{int v,nxt;}e[MAXN*2];
	int cnt,head[MAXN];
	inline void add(int x,int y){e[++cnt]={y,head[x]};head[x]=cnt;}
	#define For(G,x) for(int ___=(G).head[x];___;___=(G).e[___].nxt)
	#define v(G) (G).e[___].v
}G;

namespace SegmentTree{
	struct node{
		int num,l,r;
		int tag;
	}t[MAXN<<2];
	void build(int x,int l,int r){
		t[x].l=l,t[x].r=r;
		t[x].num=0,t[x].tag=0;
		if(l==r)return;
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
	}
	void pushdown(int x){
		if(t[x].tag){
			t[x<<1].tag^=t[x].tag;
			t[x<<1].num^=t[x].tag;
			t[x<<1|1].tag^=t[x].tag;
			t[x<<1|1].num^=t[x].tag;
			t[x].tag=0;
		}
	}
	void update(int x,int l,int r,int val){
		if(t[x].l>r||t[x].r<l)return;
		if(l<=t[x].l&&t[x].r<=r){t[x].num^=val;t[x].tag^=val;return;}
		pushdown(x);update(x<<1,l,r,val);update(x<<1|1,l,r,val);
	}
	int query(int x,int pos){
		if(t[x].l==t[x].r)return t[x].num;
		pushdown(x);
		int mid=t[x].l+t[x].r>>1;
		if(pos<=mid)return query(x<<1,pos);
		else return query(x<<1|1,pos);
	}
}

int fa[MAXN];
int dep[MAXN];
int size[MAXN];
int top[MAXN];
int dfn[MAXN];
int v[MAXN];
int cnt=0;

void dfs1(int x,int f){
	fa[x]=f,dep[x]=dep[f]+1;size[x]=1;
	For(G,x)if(v(G)!=f)dfs1(v(G),x),size[x]+=size[v(G)];
}

void dfs2(int x,int f){
	dfn[x]=++cnt;top[x]=f;SegmentTree::update(1,cnt,cnt,v[x]);
	int MAX=-1,s=-1;
	For(G,x) if(v(G)!=fa[x]&&size[v(G)]>MAX) MAX=size[v(G)], s=v(G);
	if(MAX!=-1)dfs2(s,f);
	For(G,x) if(v(G)!=fa[x]&&v(G)!=s)dfs2(v(G),v(G));
}

inline void update(int x,int y,int v){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		SegmentTree::update(1,dfn[top[x]],dfn[x],v);
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])
		swap(x,y);
	SegmentTree::update(1,dfn[x],dfn[y],v);
	return;
}

inline int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]])
			swap(u,v);
		v=fa[top[v]];
	}
	return dep[u]<dep[v]?u:v;
}

const int MAXSIZE=31;

struct basis{
	int b[MAXSIZE];
	void init(){memset(b,0,sizeof b);}
	bool insert(int x){
		for(int i=MAXSIZE-1;i>=0;i--){
			if(!(x&(1<<i)))continue;
			if(!b[i]){b[i]=x;return true;}
			x^=b[i];
		}
		return false;
	}
}B;

int main(void){
	n=read(),q=read();
	for(int i=1;i<=n;i++)
		v[i]=read();
	for(int i=1;i<n;i++){
		static int x,y;
		x=read(),y=read();
		G.add(x,y),G.add(y,x);
	}
	SegmentTree::build(1,1,n);
	dfs1(1,-1),dfs2(1,1);
	while(q--){
		static char opt;
		static int x,y,z;
		do
			opt=getchar();
		while(opt!='Q'&&opt!='U');
		switch(opt){
			case 'U':{
				x=read(),y=read(),z=read();
				update(x,y,z);
				break;
			}
			case 'Q':{
				x=read(),y=read();
				int lca=LCA(x,y),dis=dep[x]+dep[y]-dep[lca]*2+1;
				if(dis>=MAXSIZE)
					puts("YES");
				else{
					B.init();
					bool flag=false;
					if(!B.insert(SegmentTree::query(1,dfn[lca])))
						flag=true;
					if(!flag)
						while(x!=lca){
							if(!B.insert(SegmentTree::query(1,dfn[x]))){
								flag=true;
								break;
							}
							x=fa[x];
						}
					if(!flag)
						while(y!=lca){
							if(!B.insert(SegmentTree::query(1,dfn[y]))){
								flag=true;
								break;
							}
							y=fa[y];
						}
					puts(flag?"YES":"NO");
				}
			}
		}
	}
	return 0;
}