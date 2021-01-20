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

const int MAXN=1e3+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;

struct Edge{
	int u,v,val;
	inline Edge(reg int u=0,reg int v=0,reg int val=0):u(u),v(v),val(val){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return val<a.val;
	}
};

struct querys{
	int k,u,v,id;
};

int n,m,q;
Edge E[MAXM];
querys Q[MAXQ];
int ans[MAXQ];
bool vis[MAXM];
map<pair<int,int>,int> M;

namespace LCT{
	const int MAXSIZE=MAXN+MAXM;
	struct Node{
		int fa,ch[2];
		int Max,val;
		int tRev;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define val(x) unit[(x)].val
		#define Max(x) unit[(x)].Max
		#define tRev(x) unit[(x)].tRev
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXSIZE];
	inline void New(reg int p,reg int v){
		fa(p)=lson(p)=rson(p)=0;
		Max(p)=val(p)=v;
		tRev(p)=false;
		return;
	}
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline void pushup(reg int p){
		Max(p)=max(max(Max(lson(p)),Max(rson(p))),val(p));
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
		for(reg int pre=0;p;pre=p,p=fa(p))
			splay(p),rson(p)=pre,pushup(p);
		return;
	}
	inline void makeRt(reg int p){
		access(p),splay(p),tRev(p)=!tRev(p);
		return;
	}
	inline void link(reg int x,reg int y){
		makeRt(x),fa(x)=y;
		return;
	}
	inline void split(reg int x,reg int y){
		makeRt(x),access(y),splay(y);
		return;
	}
	inline void cut(reg int x,reg int y){
		split(x,y);
		fa(x)=lson(y)=0;
		return;
	}
	inline int find(reg int x){
		access(x),splay(x),pushdown(x);
		while(lson(x))
			x=lson(x),pushdown(x);
		return x;
	}
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i){
		E[i].u=read(),E[i].v=read(),E[i].val=read();
		if(E[i].u>E[i].v)
			swap(E[i].u,E[i].v);
	}
	sort(E+1,E+m+1);
	for(reg int i=1;i<=m;++i)
		M[make_pair(E[i].u,E[i].v)]=i;
	for(reg int i=1;i<=q;++i){
		Q[i].k=read(),Q[i].u=read(),Q[i].v=read();
		if(Q[i].u>Q[i].v)
			swap(Q[i].u,Q[i].v);
		if(Q[i].k==2){
			reg int id=M[make_pair(Q[i].u,Q[i].v)];
			vis[id]=true;
			Q[i].id=id;
		}
	}
	E[0].val=0;
	for(reg int i=1;i<=n+m;++i)
		LCT::New(i,i<=n?0:(i-n));
	reg int cnt=0;
	for(reg int i=1;i<=m&&cnt<n-1;++i)
		if(!vis[i]&&LCT::find(E[i].u)!=LCT::find(E[i].v))
			++cnt,LCT::link(E[i].u,i+n),LCT::link(E[i].v,i+n);
	for(reg int i=q;i>=1;--i)
		if(Q[i].k==1)
			LCT::split(Q[i].u,Q[i].v),ans[i]=E[LCT::Max(Q[i].v)].val;
		else{
			LCT::split(Q[i].u,Q[i].v);
			reg int id=Q[i].id,Max=LCT::Max(Q[i].v);
			if(E[id]<E[Max]){
				LCT::cut(E[Max].u,Max+n),LCT::cut(E[Max].v,Max+n);
				LCT::link(Q[i].u,id+n),LCT::link(Q[i].v,id+n);
			}
		}
	for(reg int i=1;i<=q;++i)
		if(Q[i].k==1)
			printf("%d\n",ans[i]);
	return 0;
}