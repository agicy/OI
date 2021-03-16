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

const int MAXN=1e5+5;

namespace LCT{
	const int MAXSIZE=MAXN<<1;
	struct Node{
		int fa,ch[2];
		int siz,sum;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define sum(x) unit[(x)].sum
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
	};
	Node unit[MAXSIZE];
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline void pushup(reg int p){
		sum(p)=sum(lson(p))+sum(rson(p))+1+siz(p);
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa(x),z=fa(y),k=get(x),w=ch(x)[!k];
		if(!isRoot(y)) ch(z)[get(y)]=x;
		ch(x)[!k]=y,ch(y)[k]=w;
		if(w) fa(w)=y;
		fa(y)=x,fa(x)=z;
		pushup(y),pushup(x);
		return;
	}
	inline void splay(reg int p){
		for(reg int f=fa(p);f=fa(p),!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		pushup(p);
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa(p)){
			splay(p);
			siz(p)-=sum(pre);
			siz(p)+=sum(rson(p));
			rson(p)=pre;
			pushup(p);
		}
		return;
	}
	inline int find(reg int p){
		access(p),splay(p);
		while(lson(p))
			p=lson(p);
		splay(p);
		return p;
	}
	inline void link(reg int x,reg int y){
		access(x),splay(x);
		access(y),splay(y);
		fa(x)=y;
		sum(y)+=sum(x),siz(y)+=sum(x);
		return;
	}
	inline void cut(reg int p){
		access(p),splay(p);
		lson(p)=fa(lson(p))=0;
		pushup(p);
		return;
	}
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN];

inline void dfs(reg int u,reg int father){
	fa[u]=father;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	return;
}

bool col[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(1,0);
	fa[1]=n+1;
	for(reg int i=1;i<=n;++i)
		LCT::link(i,fa[i]);
	m=read();
	while(m--){
		static int opt,u;
		opt=read(),u=read();
		switch(opt){
			case 0:{
				if(col[u]){
					reg int rt=LCT::find(u+n+1);
					writeln(LCT::sum(LCT::rson(rt)));
				}
				else{
					reg int rt=LCT::find(u);
					writeln(LCT::sum(LCT::rson(rt)));
				}
				break;
			}
			case 1:{
				if(col[u]){
					LCT::cut(u+n+1);
					LCT::link(u,fa[u]);
				}
				else{
					LCT::cut(u);
					LCT::link(u+n+1,fa[u]+n+1);
				}
				col[u]=!col[u];
				break;
			}
		}
	}
	flush();
	return 0;
}