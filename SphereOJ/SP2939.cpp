#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

int dep[MAXN];

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
		ll Min,val,h;
		Heap Q;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define Min(x) unit[(x)].Min
		#define val(x) unit[(x)].val
		#define h(x) unit[(x)].h
		#define Q(x) unit[(x)].Q
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
		val(p)=min(Q(p).top(),min(val(lson(p)),val(rson(p))));
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
			if(min(Q(rson(p)).top(),val(rson(p)))<inf/10)
				Q(p).push(min(Q(rson(p)).top(),val(rson(p))));
			rson(p)=pre;
			if(min(Q(rson(p)).top(),val(rson(p)))<inf/10)
				Q(p).pop(min(Q(rson(p)).top(),val(rson(p))));
			h(p)=Q(p).top()-(dep[p]<<1);
			pushup(p);
		}
		return;
	}
}

inline void dfs(reg int u,reg int father){
    LCT::fa(u)=father;
	dep[u]=dep[father]+1;
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
	for(reg int i=0;i<=n;++i){
		LCT::val(i)=LCT::Min(i)=LCT::h(i)=inf;
		LCT::Q(i).push(inf);
	}
	reg int q=read();
	while(q--){
		static int opt,x;
		opt=read(),x=read();
		switch(opt){
			case 0:{
				if(col[x]){
					LCT::access(x),LCT::splay(x);
					LCT::Q(x).pop(LCT::Q(x).top());
					LCT::h(x)=LCT::Q(x).top()-(dep[x]<<1);
					LCT::pushup(x);
				}
				else{
					LCT::access(x),LCT::splay(x);
					LCT::Q(x).push(dep[x]),LCT::h(x)=-dep[x];
					LCT::pushup(x);
				}
				col[x]=!col[x];
				break;
			}
			case 1:{
				LCT::access(x),LCT::splay(x);
				printf("%lld\n",LCT::Min(x)>inf/10?-1:dep[x]+LCT::Min(x));
				break;
			}
		}
	}
	return 0;
}