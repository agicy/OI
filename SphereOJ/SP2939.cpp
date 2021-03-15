#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const ll inf=1e16;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];

inline void dfs(reg int u,reg int father){
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	return;
}

struct Heap{
	priority_queue<ll,vector<ll>,greater<ll>/**/> p,q;
	inline void push(ll x){
		return p.push(x);
	}
	inline void pop(ll x){
		return q.push(x);
	}
	inline ll top(void){
		while(!q.empty()&&p.top()==q.top())
			p.pop(),q.pop();
		return p.top();
	}
};

namespace LCT{
	const int MAXSIZE=MAXN;
	struct Node{
		int fa,ch[2];
		ll Min,pp,h;
		Heap Q;
		bool tRev;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define Min(x) unit[(x)].Min
		#define pp(x) unit[(x)].pp
		#define h(x) unit[(x)].h
		#define Q(x) unit[(x)].Q
		#define tRev(x) unit[(x)].tRev
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXSIZE];
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline void pushup(reg int p){
		Min(p)=min(h(p),min(Min(lson(p)),Min(rson(p))));
		pp(p)=min(Q(p).top(),min(pp(lson(p)),pp(rson(p))));
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa(x),z=fa(y),k=get(x),w=ch(x)[!k];
		if(!isRoot(y)) ch(z)[get(y)]=x;
		ch(x)[!k]=y;
		ch(y)[k]=w;
		if(w) fa(w)=y;
		fa(y)=x,fa(x)=z;
		pushup(y),pushup(x);
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
		if(!isRoot(p)) update(fa(p));
		pushdown(p);
		return;
	}
	inline void splay(reg int p){
		update(p);
		for(reg int f=fa(p);f=fa(p),!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		pushup(p);
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa(p)){
			splay(p);
			if(min(Q(rson(p)).top(),pp(rson(p)))<inf/10)
				Q(p).push(min(Q(rson(p)).top(),pp(rson(p))));
			rson(p)=pre;
			if(min(Q(rson(p)).top(),pp(rson(p)))<inf/10)
				Q(p).push(min(Q(rson(p)).top(),pp(rson(p))));
			h(p)=Q(p).top()-(dep[p]<<1);
			pushup(p);
		}
		return;
	}
}

bool col[MAXN];

signed main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(1,0);
	for(reg int i=1;i<=n;++i)
		LCT::fa(i)=fa[i];
	for(reg int i=0;i<=n;++i){
		LCT::pp(i)=LCT::Min(i)=inf;
		LCT::Q(i).push(inf),LCT::h(i)=inf;
	}
	reg int q=read();
	while(q--){
		static int opt,v;
		opt=read(),v=read();
		switch(opt){
			case 0:{
				if(col[v]){
					LCT::access(v),LCT::splay(v);
					LCT::Q(v).pop(LCT::Q(v).top());
					LCT::h(v)=LCT::Q(v).top()-(dep[v]<<1);
					LCT::pushup(v);
				}
				else{
					LCT::access(v),LCT::splay(v);
					LCT::Q(v).push(dep[v]),LCT::h(v)=-dep[v];
					LCT::pushup(v);
				}
				col[v]=!col[v];
				break;
			}
			case 1:{
				LCT::access(v),LCT::splay(v);
				printf("%lld\n",LCT::Min(v)>inf/10?-1:dep[v]+LCT::Min(v));
				break;
			}
		}
	}
	return 0;
}