#include <bits/stdc++.h>
using namespace std;
#define reg register
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

namespace LCT{
	#define lson (ch[p][0])
	#define rson (ch[p][1])
	int fa[MAXN],ch[MAXN][2];
	int size[MAXN];
	int sum[MAXN],val[MAXN];
	bool tag[MAXN];
	inline bool get(reg int p){
		return ch[fa[p]][1]==p;
	}
	inline bool isRoot(reg int p){
		return ch[fa[p]][0]!=p&&ch[fa[p]][1]!=p;
	}
	inline void pushup(reg int p){
		sum[p]=sum[lson]^sum[rson]^val[p];
		size[p]=size[lson]+size[rson]+1;
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa[x],z=fa[y],dir=get(x),w=ch[x][dir^1];
		fa[x]=z;
		if(!isRoot(y))
			ch[z][get(y)]=x;
		fa[y]=x,ch[x][dir^1]=y;
		fa[w]=y,ch[y][dir]=w;
		pushup(y),pushup(x),pushup(z);
		return;
	}
	inline void pushdown(reg int p){
		if(tag[p]){
			tag[lson]^=1,tag[rson]^=1;
			swap(lson,rson);
			tag[p]=0;
		}
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
	inline void makeRoot(reg int p){
		access(p),splay(p),tag[p]^=1,pushdown(p);
		return;
	}
	inline int find(reg int p){
		access(p),splay(p),pushdown(p);
		while(lson)
			pushdown(p=lson);
		splay(p);
		return p;
	}
	inline void link(reg int x,reg int y){
		makeRoot(x);
		if(find(x)!=find(y))
			fa[x]=y;
		return;
	}
	inline void cut(reg int x,reg int y){
		makeRoot(x);
		if(find(y)!=x||size[x]>2)
			return;
		fa[y]=ch[x][1]=0,pushup(x);
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void Update(reg int x,reg int y){
		splay(x),val[x]=y,pushup(x);
		return;
	}
	inline int Query(reg int x,reg int y){
		split(x,y);
		return sum[y]^sum[ch[y][1]];
	}
	#undef lson
	#undef rson
}

int n,m;
using LCT::sum;
using LCT::val;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		val[i]=sum[i]=read();
	while(m--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 0:{
				printf("%d\n",LCT::Query(x,y));
				break;
			}
			case 1:{
				LCT::link(x,y);
				break;
			}
			case 2:{
				LCT::cut(x,y);
				break;
			}
			case 3:{
				LCT::Update(x,y);
				break;
			}
			default:break;
		}
	}
	return 0;
}