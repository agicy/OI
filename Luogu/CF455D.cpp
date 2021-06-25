#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush()(fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

namespace MY_RAND{
	typedef unsigned int uint;
	static uint x=123456789,y=362436069,z=521288629;
	inline uint get(void){
		x^=x<<16;
		x^=x>>5;
		x^=x<<1;
		reg uint t=x;
		x=y;
		y=z;
		z=t^x^y;
		return z;
	}
}

const int MAXN=1e5+5;

namespace FHQTreap{
	const int MAXSIZE=MAXN*2;
	struct Node{
		int fa,lson,rson;
		int siz,val;
		int id;
		#define fa(x) unit[(x)].fa
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define id(x) unit[(x)].id
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		if(lson(p))
			fa(lson(p))=p;
		if(rson(p))
			fa(rson(p))=p;
		return;
	}
	inline int getRnk(reg int p){
		reg int res=1+siz(lson(p));
		while(fa(p)){
			if(p!=lson(fa(p)))
				res+=1+siz(lson(fa(p)));
			p=fa(p);
		}
		return res;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(MY_RAND::get()%(siz(x)+siz(y))<siz(x)){
			fa(rson(x))=0;
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			fa(lson(y))=0;
			lson(y)=merge(x,lson(y));
			pushup(y);
			return y;
		}
	}
	inline void split_s(reg int p,reg int k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(siz(lson(p))<k){
			x=p;
			fa(rson(x))=0;
			split_s(rson(x),k-siz(lson(p))-1,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			fa(lson(y))=0;
			split_s(lson(y),k,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline void split_v(reg int p,reg int v,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		reg int k=getRnk(id(p));
		if(k<v){
			x=p;
			fa(rson(x))=0;
			split_v(rson(x),v,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			fa(lson(y))=0;
			split_v(lson(y),v,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline int kth(reg int p,reg int k){
		while(true)
			if(k<=siz(lson(p)))
				p=lson(p);
			else{
				k-=siz(lson(p))+1;
				if(!k)
					return p;
				else
					p=rson(p);
			}
		return -1;
	}
}

int n,q;
int rt,rts[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		reg int x=read();
		FHQTreap::unit[i]=FHQTreap::Node{0,0,0,1,0,i+n};
		FHQTreap::unit[i+n]=FHQTreap::Node{0,0,0,1,x,i};
		rts[x]=FHQTreap::merge(rts[x],i);
		rt=FHQTreap::merge(rt,i+n);
	}
	q=read();
	reg int lastans=0;
	while(q--){
		static int opt,l,r,k;
		opt=read();
		switch(opt){
			case 1:{
				l=(read()+lastans-1)%n+1,r=(read()+lastans-1)%n+1;
				if(l>r)
					swap(l,r);
				reg int p=FHQTreap::kth(rt,r);
				reg int pp=FHQTreap::id(p);
				reg int rnk=FHQTreap::getRnk(pp);
				reg int c=FHQTreap::val(p);
				static int rt1,rt2,rt3,rt4,rt5,rt6;
				FHQTreap::split_s(rts[c],rnk-1,rt1,rt2);
				FHQTreap::split_s(rt2,1,rt3,rt4);
				FHQTreap::split_v(rt1,l,rt5,rt6);
				rts[c]=FHQTreap::merge(FHQTreap::merge(rt5,rt3),FHQTreap::merge(rt6,rt4));
				FHQTreap::split_s(rt,r-1,rt1,rt2);
				FHQTreap::split_s(rt2,1,rt3,rt4);
				FHQTreap::split_s(rt1,l-1,rt5,rt6);
				rt=FHQTreap::merge(FHQTreap::merge(rt5,rt3),FHQTreap::merge(rt6,rt4));
				break;
			}
			case 2:{
				l=(read()+lastans-1)%n+1,r=(read()+lastans-1)%n+1,k=(read()+lastans-1)%n+1;
				if(l>r)
					swap(l,r);
				static int rt1,rt2,rt3,rt4;
				FHQTreap::split_v(rts[k],l,rt1,rt2);
				FHQTreap::split_v(rt2,r+1,rt3,rt4);
				lastans=FHQTreap::siz(rt3);
				rts[k]=FHQTreap::merge(rt1,FHQTreap::merge(rt3,rt4));
				writeln(lastans);
				break;
			}
		}
	}
	flush();
	return 0;
}
