#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
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
	const int MAXSIZE=MAXN;
	struct Node{
		int lson,rson,siz;
		int val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int v){
		reg int p=++tot;
		lson(p)=rson(p)=0,siz(p)=1;
		val(p)=v;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void split(reg int p,reg int v,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(val(p)<=v){
			x=p;
			split(rson(x),v,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			split(lson(y),v,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(MY_RAND::get()%(siz(x)+siz(y))<siz(x)){
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
	inline int kth(reg int p,reg int k){
		while(true){
			if(k<=siz(lson(p)))
				p=lson(p);
			else{
				k-=siz(lson(p))+1;
				if(!k)
					return val(p);
				else
					p=rson(p);
			}
		}
		return -1;
	}
	inline int insert(reg int p,reg int v){
		static int x,y;
		split(p,v,x,y);
		return merge(merge(x,New(v)),y);
	}
	inline int del(reg int p,reg int w){
		static int x,y,z;
		split(p,w,x,z);
		split(x,w-1,x,y);
		return merge(merge(x,merge(lson(y),rson(y))),z);
	}
	int ans;
	inline int rnk(reg int p,reg int v){
		static int x,y;
		split(p,v-1,x,y);
		ans=siz(x);
		return merge(x,y);
	}
	inline int pre(reg int p,reg int v){
		static int x,y;
		split(p,v-1,x,y);
		reg int id=x;
		while(rson(id))
			id=rson(id);
		ans=val(id);
		return merge(x,y);
	}
	inline int suf(reg int p,reg int v){
		static int x,y;
		split(p,v,x,y);
		reg int id=y;
		while(lson(id))
			id=lson(id);
		ans=val(id);
		return merge(x,y);
	}
}

int main(void){
	srand(time(0));
	reg int n=read();
	using namespace FHQTreap;
	reg int rt=0;
	while(n--){
		static int opt,x;
		opt=read(),x=read();
		switch(opt){
			case 1:{
				rt=insert(rt,x);
				break;
			}
			case 2:{
				rt=del(rt,x);
				break;
			}
			case 3:{
				rt=rnk(rt,x);
				writeln(ans+1);
				break;
			}
			case 4:{
				writeln(kth(rt,x));
				break;
			}
			case 5:{
				rt=pre(rt,x);
				writeln(ans);
				break;
			}
			case 6:{
				rt=suf(rt,x);
				writeln(ans);
				break;
			}
		}
	}
	flush();
	return 0;
}