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
const int inf=0x3f3f3f3f;

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

namespace LCT{
	const int MAXSIZE=2*MAXN;
	struct Node{
		int fa,ch[2];
		int Max,val;
		multiset<int> S;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define Max(x) unit[(x)].Max
		#define val(x) unit[(x)].val
		#define S(x) unit[(x)].S
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
		Max(p)=max(max(Max(lson(p)),Max(rson(p))),max(val(p),*S(p).rbegin()));
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
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa(p)){
			splay(p);
			S(p).erase(S(p).find(Max(pre))),S(p).insert(Max(rson(p)));
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
		S(y).insert(Max(x));
		pushup(y);
		return;
	}
	inline void cut(reg int p){
		access(p),splay(p);
		lson(p)=fa(lson(p))=0;
		pushup(p);
		return;
	}
	inline void update(reg int p,reg int w){
		access(p),splay(p);
		val(p)=w;
		pushup(p);
		return;
	}
}

bool col[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(1,n+1);
	for(reg int i=0;i<=(n+1)<<1;++i)
		LCT::S(i).insert(-inf),LCT::Max(i)=-inf;
	for(reg int i=1;i<=n;++i){
		col[i]=read();
		if(col[i])
			LCT::link(i+n+1,fa[i]+n+1);
		else
			LCT::link(i,fa[i]);
	}
	for(reg int i=1;i<=n;++i){
		static int w;
		w=read();
		LCT::update(i,w),LCT::update(i+n+1,w);
	}
	m=read();
	while(m--){
		static int opt,u,w;
		opt=read(),u=read();
		switch(opt){
			case 0:{
				if(col[u]){
					reg int rt=LCT::find(u+n+1);
					writeln(LCT::Max(LCT::rson(rt)));
				}
				else{
					reg int rt=LCT::find(u);
					writeln(LCT::Max(LCT::rson(rt)));
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
			case 2:{
				w=read();
				LCT::update(u,w),LCT::update(u+n+1,w);
				break;
			}
		}
	}
	flush();
	return 0;
}