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

const int MAXN=2e5+5;

namespace FHQTreap{
	const int MAXSIZE=MAXN*70;
	struct Node{
		int key;
		int ch[2];
		int siz;
		int val;
		ll sum;
		bool tag;
		#define key(x) unit[(x)].key
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int v){
		reg int p=++tot;
		val(p)=sum(p)=v;
		key(p)=rand(),siz(p)=1;
		return p;
	}
	inline int copy(reg int p){
		reg int q=New(0);
		unit[q]=unit[p];
		return q;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
		return;
	}
	inline void pushdown(reg int p){
		if(tag(p)){
			if(lson(p))
				lson(p)=copy(lson(p));
			if(rson(p))
				rson(p)=copy(rson(p));
			swap(lson(p),rson(p));
			if(lson(p))
				tag(lson(p))^=1;
			if(rson(p))
				tag(rson(p))^=1;
			tag(p)=false;
		}
		return;
	}
	inline void split(reg int p,reg int k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		pushdown(p);
		if(siz(lson(p))<k){
			x=copy(p);
			split(rson(x),k-siz(lson(p))-1,rson(x),y);
			pushup(x);
		}
		else{
			y=copy(p);
			split(lson(y),k,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		pushdown(x),pushdown(y);
		if(key(x)<key(y)){
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			lson(y)=merge(x,lson(y));
			pushup(y);
			return y;
		}
	}
}

int cnt,rt[MAXN];

int main(void){
	srand(time(0));
	reg int n=read();
	reg ll lastans=0;
	using namespace FHQTreap;
	while(n--){
		static int opt,v,p,x,l,r;
		v=read(),opt=read();
		switch(opt){
			case 1:{
				p=read()^lastans,x=read()^lastans;
				int rt1,rt2;
				split(rt[v],p,rt1,rt2);
				rt[++cnt]=merge(merge(rt1,New(x)),rt2);
				break;
			}
			case 2:{
				p=read()^lastans;
				int rt1,mid,rt2;
				split(rt[v],p,rt1,rt2);
				split(rt1,p-1,rt1,mid);
				rt[++cnt]=merge(rt1,rt2);
				break;
			}
			case 3:{
				l=read()^lastans,r=read()^lastans;
				int rt1,mid,rt2;
				split(rt[v],r,rt1,rt2);
				split(rt1,l-1,rt1,mid);
				tag(mid)^=1;
				rt[++cnt]=merge(merge(rt1,mid),rt2);
				break;
			}
			case 4:{
				l=read()^lastans,r=read()^lastans;
				int rt1,mid,rt2;
				split(rt[v],r,rt1,rt2);
				split(rt1,l-1,rt1,mid);
				lastans=sum(mid);
				printf("%lld\n",lastans);
				rt[++cnt]=merge(merge(rt1,mid),rt2);
				break;
			}
		}
	}
	return 0;
}