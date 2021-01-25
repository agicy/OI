#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXC=MAXN+2*MAXM;

struct querys{
	int opt,u,v,l,r;
};

int n,m;
vector<int> V;
int c[MAXN];
querys q[MAXM];

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
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=3e7+5;
	struct Node{
		int lson,rson;
		int cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	Node unit[MAXSIZE];
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=++tot;
		cnt(p)+=val;
		if(l!=r){
			if(pos<=mid)
				update(lson(p),l,mid,pos,val);
			else
				update(rson(p),mid+1,r,pos,val);
		}
		return;
	}
	inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p) return 0;
		if(L<=l&&r<=R)
			return cnt(p);
		if(L<=mid&&mid<R)
			return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	#undef mid
}

int C;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,rt[MAXC];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,C,pos,val);
		return;
	}
	inline int query(reg int id,reg int l,reg int r){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=SegmentTree::query(rt[i],1,C,l,r);
		return res;
	}
}

inline int query(int x,int y,reg int l,reg int r){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=BIT::query(r,dfn[top[y]],dfn[y])-BIT::query(l-1,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res+=BIT::query(r,dfn[x],dfn[y])-BIT::query(l-1,dfn[x],dfn[y]);
	return res;
}

int main(void){
	printf("%.3lf M\n",sizeof(SegmentTree::unit)/1048576.0);
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		c[i]=read();
		V.push_back(c[i]);
	}
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	for(reg int i=1;i<=m;++i){
		static char opt;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'C':{
				q[i].opt=1,q[i].u=read(),q[i].l=read();
				V.push_back(q[i].l);
				break;
			}
			case 'Q':{
				q[i].opt=2,q[i].u=read(),q[i].v=read(),q[i].l=read(),q[i].r=read();
				V.push_back(q[i].l),V.push_back(q[i].r);
				break;
				break;
			}
		}
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		c[i]=lower_bound(V.begin(),V.end(),c[i])-V.begin()+1;
	}
	for(reg int i=1;i<=m;++i)
		if(q[i].opt==1)
			q[i].l=lower_bound(V.begin(),V.end(),q[i].l)-V.begin()+1;
		else{
			q[i].l=lower_bound(V.begin(),V.end(),q[i].l)-V.begin()+1;
			q[i].r=lower_bound(V.begin(),V.end(),q[i].r)-V.begin()+1;
		}
	dfs1(1,0),dfs2(1,0,1);
	C=V.size();
	BIT::Init(C);
	for(reg int i=1;i<=n;++i)
		BIT::update(c[i],dfn[i],1);
	for(reg int i=1;i<=m;++i){
		if(q[i].opt==1){
			reg int u=q[i].u;
			BIT::update(c[u],dfn[u],-1);
			c[u]=q[i].l;
			BIT::update(c[u],dfn[u],1);
		}
		else{
			reg int res=query(q[i].u,q[i].v,q[i].l,q[i].r);
			printf("%d\n",res);
		}
	}
	return 0;
}