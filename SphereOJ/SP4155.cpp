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

const int MAXN=3e4+5;

int n,q;

namespace LCT{
	struct Node{
		int fa,ch[2];
		int sum,val;
		bool tRev;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
		#define tRev(x) unit[(x)].tRev
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXN];
	inline void New(reg int p,reg int v){
		fa(p)=lson(p)=rson(p);
		sum(p)=val(p)=v;
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
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
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
	inline void makeroot(reg int p){
		access(p),splay(p),Rev(p);
		return;
	}
	inline void split(reg int x,reg int y){
		makeroot(x),access(y),splay(y);
		return;
	}
	inline void link(reg int x,reg int y){
		split(x,y),fa(x)=y,pushup(y);
		return;
	}
	inline int find(reg int p){
		access(p),splay(p),pushdown(p);
		while(lson(p))
			pushdown(p=lson(p));
		splay(p);
		return p;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int w;
		w=read();
		LCT::New(i,w);
	}
	q=read();
	while(q--){
		static char opt;
		static int u,v,x;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'b':{
				u=read(),v=read();
				if(LCT::find(u)==LCT::find(v))
					puts("no");
				else
					puts("yes"),LCT::link(u,v);
				break;
			}
			case 'p':{
				u=read(),x=read();
				LCT::splay(u);
				LCT::val(u)=x;
				LCT::pushup(u);
				break;
			}
			case 'e':{
				u=read(),v=read();
				if(LCT::find(u)!=LCT::find(v))
					puts("impossible");
				else{
					LCT::split(u,v);
					printf("%d\n",LCT::sum(v));
				}
				break;
			}
		}
	}
	return 0;
}