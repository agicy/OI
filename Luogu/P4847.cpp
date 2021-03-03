#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e5+5;

namespace FHQTreap{
	struct Node{
		int fa,lson,rson,siz;
		int val;
		ll sum;
		#define fa(x) unit[(x)].fa
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXN];
	inline int New(reg int v){
		reg int p=++tot;
		fa(p)=lson(p)=rson(p)=0;
		siz(p)=1;
		val(p)=sum(p)=v;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
		if(lson(p))
			fa(lson(p))=p;
		if(rson(p))
			fa(rson(p))=p;
		return;
	}
	inline void split(reg int p,reg int k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(siz(lson(p))<k){
			x=p;
			split(rson(x),k-siz(lson(p))-1,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			split(lson(y),k,x,lson(y));
			pushup(y);
		}
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
	inline int getFa(reg int p){
		while(fa(p))
			p=fa(p);
		return p;
	}
	inline int getRnk(reg int p){
		reg int res=siz(lson(p))+1;
		while(fa(p)){
			if(p==rson(fa(p)))
				res+=siz(lson(fa(p)))+1;
			p=fa(p);
		}
		return res;
	}
}

using namespace FHQTreap;

int n,m;
int id[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		id[i]=New(read());
	while(m--){
		static char opt;
		static int x,y;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'M':{
				x=id[read()],y=id[read()];
				reg int rx=getFa(x),ry=getFa(y);
				if(rx!=ry)
					merge(ry,rx);
				break;
			}
			case 'D':{
				x=id[read()];
				reg int rt=getFa(x);
				reg int k=getRnk(x)-1;
				static int rt1,rt2;
				split(rt,k,rt1,rt2);
				fa(rt1)=fa(rt2)=0;
				break;
			}
			case 'Q':{
				x=id[read()],y=id[read()];
				reg int rx=getFa(x),ry=getFa(y);
				if(rx!=ry)
					writeln(-1);
				else{
					reg int rt=rx;
					int rk1=getRnk(x),rk2=getRnk(y);
					if(rk1>rk2){
						swap(x,y);
						swap(rk1,rk2);
					}
					static int rt1,mid,rt2;
					split(rt,rk1-1,rt1,rt2);
					fa(rt1)=fa(rt2)=0;
					split(rt2,rk2-rk1+1,mid,rt2);
					fa(mid)=fa(rt2)=0;
					writeln(sum(mid));
					merge(merge(rt1,mid),rt2);
				}
			}
		}
	}
	flush();
	return 0;
}