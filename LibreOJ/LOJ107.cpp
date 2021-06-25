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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
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

const int MAXN=3e5+5;

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
	int top,S[MAXSIZE];
	inline int getId(void){
		if(top)
			return S[top--];
		else
			return ++tot;
	}
	inline int New(reg int v){
		reg int p=getId();
		lson(p)=rson(p)=0,siz(p)=1;
		val(p)=v;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(rand()%(siz(x)+siz(y))<siz(x)){
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
	inline void insert(reg int &rt,reg int v){
		static int rt1,rt2;
		split(rt,v,rt1,rt2);
		rt=merge(merge(rt1,New(v)),rt2);
		return;
	}
	inline void del(reg int &rt,reg int v){
		static int rt1,mid,rt2;
		split(rt,v-1,rt1,mid);
		split(mid,v,mid,rt2);
		rt=merge(merge(rt1,merge(lson(mid),rson(mid))),rt2);
		S[++top]=mid;
		return;
	}
	inline int kth(reg int rt,reg int k){
		reg int p=rt;
		while(true)
			if(k<=siz(lson(p)))
				p=lson(p);
			else{
				k-=siz(lson(p))+1;
				if(!k)
					return val(p);
				else
					p=rson(p);
			}
		return -1;
	}
	inline int getRnk(reg int &rt,reg int v){
		static int rt1,rt2;
		split(rt,v-1,rt1,rt2);
		reg int res=siz(rt1);
		rt=merge(rt1,rt2);
		return res;
	}
	inline int pre(reg int &rt,reg int v){
		static int rt1,rt2;
		split(rt,v-1,rt1,rt2);
		reg int res;
		if(!siz(rt1))
			res=-1;
		else{
			reg int p=rt1;
			while(rson(p))
				p=rson(p);
			res=val(p);
		}
		rt=merge(rt1,rt2);
		return res;
	}
	inline int suf(reg int &rt,reg int v){
		static int rt1,rt2;
		split(rt,v,rt1,rt2);
		reg int res;
		if(!siz(rt2))
			res=-1;
		else{
			reg int p=rt2;
			while(lson(p))
				p=lson(p);
			res=val(p);
		}
		rt=merge(rt1,rt2);
		return res;
	}
}

int rt;

int main(void){
	reg int n=read();
	while(n--){
		static int opt,x;
		opt=read(),x=read();
		switch(opt){
			case 0:{
				FHQTreap::insert(rt,x);
				break;
			}
			case 1:{
				FHQTreap::del(rt,x);
				break;
			}
			case 2:{
				writeln(FHQTreap::kth(rt,x));
				break;
			}
			case 3:{
				writeln(FHQTreap::getRnk(rt,x));
				break;
			}
			case 4:{
				writeln(FHQTreap::pre(rt,x));
				break;
			}
			case 5:{
				writeln(FHQTreap::suf(rt,x));
				break;
			}
		}
	}
	flush();
	return 0;
}