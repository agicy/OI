#include <bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=10000+5;

namespace LCT{
	#define lson (ch[p][0])
	#define rson (ch[p][1])
	int fa[MAXN],ch[MAXN][2];
	int size[MAXN];
	bool tag[MAXN];
	inline bool get(reg int p){
		return ch[fa[p]][1]==p;
	}
	inline bool isRoot(reg int p){
		return ch[fa[p]][0]!=p&&ch[fa[p]][1]!=p;
	}
	inline void pushup(reg int p){
		size[p]=size[lson]+size[rson]+1;
		return;
	}
	inline void Swap(reg int p){
		swap(lson,rson);
		tag[p]^=1;
		return;
	}
	inline void pushdown(reg int p){
		if(tag[p]){
			if(lson)
				Swap(lson);
			if(rson)
				Swap(rson);
			tag[p]=false;
		}
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
		if(!isRoot(y))
			ch[z][get(y)]=x;
		ch[x][!k]=y;
		ch[y][k]=w;
		if(w)
			fa[w]=y;
		fa[y]=x,fa[x]=z;
		pushup(y);
		return;
	}
	inline void update(reg int p){
		if(!isRoot(p))
			update(fa[p]);
		pushdown(p);
		return;
	}
	inline void splay(reg int p){
		update(p);
		for(reg int f=fa[p];f=fa[p],!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		pushup(p);
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa[p])
			splay(p),rson=pre,pushup(p);
		return;
	}
	inline int find(reg int p){
		access(p),splay(p),pushdown(p);
		while(lson)
			pushdown(p=lson);
		splay(p);
		return p;
	}
	inline void makeRoot(reg int p){
		access(p),splay(p),Swap(p);
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void link(reg int x,reg int y){
		makeRoot(x);
		fa[x]=y;
		return;
	}
	inline void cut(reg int x,reg int y){
		split(x,y);
		fa[x]=ch[y][0]=0;
		return;
	}
	#undef lson
	#undef rson
}

int n,m;

int main(void){
	scanf("%d%d",&n,&m);
	while(m--){
		static char opt[16];
		static int u,v;
		scanf("%s%d%d",opt,&u,&v);
		switch(opt[0]){
			case 'C':{
				LCT::link(u,v);
				break;
			}
			case 'D':{
				LCT::cut(u,v);
				break;
			}
			case 'Q':{
				puts(LCT::find(u)==LCT::find(v)?"Yes":"No");
				break;
			}
			default:break;
		}
	}
	return 0;
}