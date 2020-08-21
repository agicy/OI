#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=3e5+5;

namespace LCT{
	struct Node{
		int fa,ch[2],size;
		int val,sum;
		bool tag;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define size(x) unit[(x)].size
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
		#define lson(x) unit[(x)].ch[0]
		#define rson(x) unit[(x)].ch[1]
	};
	Node unit[MAXN];
	inline void pushup(reg int x){
		sum(x)=sum(lson(x))^sum(rson(x))^val(x);
		size(x)=size(lson(x))+size(rson(x))+1;
		return;
	}
	inline bool check(reg int x){
		return ch(fa(x))[1]==x;
	}
	inline bool isroot(reg int x){
		return ch(fa(x))[0]!=x&&ch(fa(x))[1]!=x;
	}
	inline void rotate(reg int x){
		reg int y=fa(x),z=fa(y),dir=check(x),w=ch(x)[!dir];
		fa(x)=z;
		if(!isroot(y))
			ch(z)[check(y)]=x;
		fa(y)=x,ch(x)[dir^1]=y;
		fa(w)=y,ch(y)[dir]=w;
		pushup(y),pushup(x);
	}
	inline void pushdown(reg int x){
		if(tag(x)){
			tag(lson(x))^=1,tag(rson(x))^=1;
			swap(lson(x),rson(x));
			tag(x)=false;
		}
		return;
	}
	inline void update(reg int x){
		if(!isroot(x))
			update(fa(x));
		pushdown(x);
		return;
	}
	inline void splay(reg int x){
		update(x);
		for(reg int f;f=fa(x),!isroot(x);rotate(x))
			if(!isroot(f))
				rotate(check(x)==check(f)?f:x);
		pushup(x);
		return;
	}
	inline void access(reg int x){
		for(reg int pre=0;x;pre=x,x=fa(x))
			splay(x),rson(x)=pre,pushup(x);
		return;
	}
	inline void makeRoot(reg int x){
		access(x),splay(x),tag(x)^=1,pushdown(x);
		return;
	}
	inline int find(reg int x){
		access(x),splay(x),pushdown(x);
		while(lson(x))
			pushdown(x=lson(x));
		splay(x);
		return x;
	}
	inline void link(reg int x,reg int y){
		makeRoot(x);
		if(find(x)!=find(y))
			fa(x)=y;
		return;
	}
	inline void cut(reg int x,reg int y){
		makeRoot(x);
		if(find(y)!=x||size(x)>2)
			return;
		fa(y)=rson(x)=0,pushup(x);
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void update(reg int x,reg int y){
		splay(x),val(x)=y,pushup(x);
		return;
	}
	inline int query(reg int x,reg int y){
		split(x,y);
		return sum(y)^sum(rson(y));
	}
}

int n,m;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		LCT::unit[i].val=read();
	while(m--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 0:{
				printf("%d\n",LCT::query(x,y));
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
				LCT::update(x,y);
				break;
			}
		}
	}
	return 0;
}