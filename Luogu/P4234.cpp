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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e4+5;
const int MAXM=2e5+5;
const int inf=0x3f3f3f3f;

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
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

struct Edge{
	int u,v,w;
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m;
Edge E[MAXM];
bool vis[MAXM];

int main(void){
	n=read(),m=read();
	if(n==1){
		puts("0");
		return 0;
	}
	for(reg int i=1;i<=m;++i){
		E[i].u=read(),E[i].v=read(),E[i].w=read();
		if(E[i].u==E[i].v)
			--i,--m;
	}
	sort(E+1,E+m+1);
	UnionFind::Init(n);
	for(reg int i=1;i<=n+m;++i)
		LCT::New(i,i<=n?inf:i-n);
	reg int cnt=n;
	reg int ans=(n==1)?0:inf;
	reg int ptr=0;
	vis[0]=true;
	for(reg int i=1;i<=m;++i){
		if(!UnionFind::search(E[i].u,E[i].v)){
			--cnt;
			UnionFind::merge(E[i].u,E[i].v);
			LCT::link(E[i].u,i+n),LCT::link(E[i].v,i+n);
		}
		else{
			LCT::split(E[i].u,E[i].v);
			reg int id=LCT::Minid(E[i].v);
			LCT::cut(E[id].u,id+n),LCT::cut(E[id].v,id+n);
			vis[id]=true;
			LCT::link(E[i].u,i+n),LCT::link(E[i].v,i+n);
		}
		if(cnt==1){
			while(vis[ptr])
				++ptr;
			ans=min(ans,E[i].w-E[ptr].w);
		}
	}
	printf("%d\n",ans);
	return 0;
}