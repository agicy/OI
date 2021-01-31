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

const int MAXN=1e4+5;
const int MAXM=1e5+5;
const int MAXC=10+1;
const int MAXNC=1e5+5;

namespace LCT{
	struct Node{
		int fa,ch[2];
		int siz;
		int Max,val;
		bool tRev;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define Max(x) unit[(x)].Max
		#define val(x) unit[(x)].val
		#define tRev(x) unit[(x)].tRev
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
	};
	Node unit[MAXNC];
	inline void New(reg int p,reg int v){
		fa(p)=lson(p)=rson(p)=0;
		siz(p)=1;
		Max(p)=val(p)=v;
		tRev(p)=false;
		return;
	}
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		Max(p)=val(p);
		if(lson(p)&&Max(lson(p))>Max(p))
			Max(p)=Max(lson(p));
		if(rson(p)&&Max(rson(p))>Max(p))
			Max(p)=Max(rson(p));
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
	inline void Rev(reg int p){
		swap(lson(p),rson(p));
		tRev(p)=!tRev(p);
		return;
	}
	inline void pushdown(reg int p){
		if(tRev(p)){
			if(lson(p))
				Rev(lson(p));
			if(rson(p))
				Rev(rson(p));
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
		access(p),splay(p),Rev(p);
		return;
	}
	inline void link(reg int x,reg int y){
		//printf("link %d %d\n",x,y);
		makeRoot(x),fa(x)=y;
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void cut(reg int x,reg int y){
		//printf("cut %d %d\n",x,y);
		split(x,y);
		fa(x)=lson(y)=0;
		pushup(y);
		return;
	}
	inline int find(reg int p){
		access(p),splay(p),pushdown(p);
		while(lson(p))
			pushdown(p=lson(p));
		splay(p);
		return p;
	}
	#undef lson
	#undef rson
}

int n,m,C,k;
int v[MAXN];
map<pair<int,int>,int> M;
int c[MAXM];
int vis[MAXN][MAXC];

inline int getId(reg int c,reg int i){
	return c*n+i;
}

int main(void){
	n=read(),m=read(),C=read(),k=read();
	for(reg int i=1;i<=n;++i){
		v[i]=read();
		for(reg int j=0;j<C;++j)
			LCT::New(getId(j,i),v[i]);
	}
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		if(u>v)
			swap(u,v);
		M[make_pair(u,v)]=w;
		++vis[u][w],++vis[v][w];
		LCT::link(getId(w,u),getId(w,v));
	}
	while(k--){
		static int opt,x,y,w;
		opt=read();
		switch(opt){
			case 0:{
				x=read(),w=read();
				for(reg int j=0;j<C;++j){
					LCT::makeRoot(getId(j,x));
					LCT::val(getId(j,x))=w;
					LCT::pushup(getId(j,x));
				}
				break;
			}
			case 1:{
				x=read(),y=read(),w=read();
				if(x>y) swap(x,y);
				if(M.find(make_pair(x,y))==M.end())
					puts("No such edge.");
				else{
					reg int id=M[make_pair(x,y)];
					--vis[x][id],--vis[y][id];
					LCT::cut(getId(id,x),getId(id,y));
					if(vis[x][w]>=2||vis[y][w]>=2){
						puts("Error 1.");
						++vis[x][id],++vis[y][id];
						LCT::link(getId(id,x),getId(id,y));
					}
					else if(LCT::find(getId(w,x))==LCT::find(getId(w,y))){
						puts("Error 2.");
						++vis[x][id],++vis[y][id];
						LCT::link(getId(id,x),getId(id,y));
					}
					else{
						M[make_pair(x,y)]=w;
						++vis[x][w],++vis[y][w];
						LCT::link(getId(w,x),getId(w,y));
						puts("Success.");
					}
				}
				break;
			}
			case 2:{
				w=read(),x=read(),y=read();
				if(LCT::find(getId(w,x))==LCT::find(getId(w,y))){
					LCT::split(getId(w,x),getId(w,y));
					printf("%d\n",LCT::Max(getId(w,y)));
				}
				else
					puts("-1");
				break;
			}
		}
	}
	return 0;
}