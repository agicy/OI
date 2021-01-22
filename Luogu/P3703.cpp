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

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}


namespace LCT{
	const int MAXSIZE=MAXN+MAXM;
	struct Node{
		int fa,ch[2];
		bool tRev;
		int id,Minid;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define tRev(x) unit[(x)].tRev
		#define Minid(x) unit[(x)].Minid
		#define id(x) unit[(x)].id
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXSIZE];
	inline void New(reg int p,reg int v){
		fa(p)=lson(p)=rson(p)=0;
		tRev(p)=false;
		Minid(p)=id(p)=v;
		return;
	}
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline void pushup(reg int p){
		Minid(p)=id(p);
		if(lson(p)&&Minid(lson(p))<Minid(p))
			Minid(p)=Minid(lson(p));
		if(rson(p)&&Minid(rson(p))<Minid(p))
			Minid(p)=Minid(rson(p));
		return;
	}
	inline void rotate(reg int p){
		if(isRoot(p))
			return;
		reg int f=fa(p),ff=fa(f),dir=get(p);
		if(!isRoot(f)) ch(ff)[get(f)]=p;
		if(ch(p)[dir^1]) fa(ch(p)[dir^1])=f;
		ch(f)[dir]=ch(p)[dir^1];
		ch(p)[dir^1]=f,fa(f)=p;
		fa(p)=ff;
		pushup(f),pushup(p);
		return;
	}
	inline void pushdown(reg int p){
		if(tRev(p)){
			swap(lson(p),rson(p));
			if(lson(p))
				tRev(lson(p))=!tRev(lson(p));
			if(rson(p))
				tRev(rson(p))=!tRev(rson(p));
			tRev(p)=false;
		}
		return;
	}
	inline void update(reg int p){
		if(!isRoot(p))
			update(fa(p));
		pushdown(p);
		return;
	}
	inline void splay(reg int p){
		update(p);
		for(reg int f;f=fa(p),!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		pushup(p);
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa(p))
			splay(p),rson(p)=pre,pushup(p);
		return;
	}
	inline void makeRoot(reg int p){
		access(p),splay(p),tRev(p)=!tRev(p);
		return;
	}
	inline void link(reg int x,reg int y){
		makeRoot(x),fa(x)=y;
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void cut(reg int x,reg int y){
		split(x,y);
		fa(x)=lson(y)=0;
		pushup(y);
		return;
	}
	inline int find(reg int p){
		access(p),splay(p);
		while(lson(p))
			pushdown(p),p=lson(p);
		return p;
	}
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
int tim,dfn[MAXN];

inline void dfs1(reg int u,reg int father){
	LCT::fa(u)=father,LCT::siz(u)=1;
	siz[u]=1;
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	dfn[u]=++tim;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
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



int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	dfs1(1,0);
	while(m--){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 1:{
				x=read();

				break;
			}
			case 2:{
				x=read(),y=read();

				break;
			}
			case 3:{
				x=read();

				break;
			}
		}
	}

	return 0;
}