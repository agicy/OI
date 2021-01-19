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

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

struct Node{
	int id,h;
	inline Node(reg int id=0,reg int h=0):id(id),h(h){
		return;
	}
	inline bool operator<(const Node& a)const{
		return h<a.h||(h==a.h&&id<a.id);
	}
};

Node a[MAXN];

namespace Splay{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int fa,ch[2];
		int siz;
		bool tag;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define tag(x) unit[(x)].tag
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	int rt;
	Node unit[MAXN];
	inline bool get(reg int p){
		return p==rson(fa(p));
	}
	inline void update(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void pushdown(reg int p){
		if(tag(p)){
			if(lson(p))
				tag(lson(p))^=1;
			if(rson(p))
				tag(rson(p))^=1;
			swap(lson(p),rson(p));
			tag(p)=false;
		}
		return;
	}
	inline void rotate(reg int p){
		reg int f=fa(p),ff=fa(f);
		reg int dir=get(p);
		pushdown(f),pushdown(p);
		ch(f)[dir]=ch(p)[dir^1];
		fa(ch(f)[dir])=f;
		ch(p)[dir^1]=f,fa(f)=p,fa(p)=ff;
		if(ff) ch(ff)[rson(ff)==f]=p;
		update(f),update(p);
		return;
	}
	inline void splay(reg int x,reg int goal){
		for(reg int f;f=fa(x),f!=goal;rotate(x)){
			pushdown(fa(f)),pushdown(f),pushdown(x);
			if(fa(f)!=goal)
				rotate(get(x)==get(f)?f:x);
		}
		if(!goal)
			rt=x;
		return;
	}
	inline void build(reg int l,reg int r,reg int father){
		if(l>r)
			return;
		if(mid<father)
			lson(father)=mid;
		else
			rson(father)=mid;
		siz(mid)=1,fa(mid)=father;
		if(l==r)
			return;
		build(l,mid-1,mid),build(mid+1,r,mid);
		update(mid);
		return;
	}
	inline int find(reg int k){
		reg int p=rt;
		while(true){
			if(tag(p))
				pushdown(p);
			if(k<=siz(lson(p))&&lson(p))
				p=lson(p);
			else{
				k-=siz(lson(p))+1;
				if(!k)
					return p;
				else
					p=rson(p);
			}
		}
		return -1;
	}
}

int n;

int main(void){
	while(n=read(),n){
		for(reg int i=2;i<=n+1;++i)
			a[i]=Node(i,read());
		a[1]=Node(1,-inf),a[n+2]=Node(n+2,inf);
		sort(a+1,a+n+3);

		using namespace Splay;
		for(reg int i=1;i<=n+2;++i)
			memset(&unit[i],0,sizeof(unit[i]));
		build(1,n+2,0);
		rt=(n+3)>>1;
		for(reg int i=2;i<=n;++i){
			splay(a[i].id,0);
			printf("%d ",siz(lson(rt)));
			reg int x=find(i-1),y=find(siz(lson(rt))+2);
			splay(x,0),splay(y,x);
			tag(lson(rson(rt)))^=1;
		}
		printf("%d\n",n);
	}
	return 0;
}