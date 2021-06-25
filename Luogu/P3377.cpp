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
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
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

const int MAXN=1e5+5;

namespace Heap{
	struct Node{
		int fa,lson,rson,dis;
		int val;
		bool del;
		#define fa(x) unit[(x)].fa
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define dis(x) unit[(x)].dis
		#define val(x) unit[(x)].val
		#define del(x) unit[(x)].del
	};
	int tot;
	Node unit[MAXN];
	inline int New(reg int v){
		reg int p=++tot;
		fa(p)=p,val(p)=v,del(p)=false;
		return p;
	}
	inline void pushup(reg int p){
		dis(p)=dis(rson(p))+1;
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(val(x)>val(y)||(val(x)==val(y)&&x>y))
			swap(x,y);
		rson(x)=merge(rson(x),y);
		if(dis(lson(x))<dis(rson(x)))
			swap(lson(x),rson(x));
		fa(lson(x))=fa(rson(x))=fa(x)=x;
		pushup(x);
		return x;
	}
	inline int top(reg int p){
		assert(!del(p));
		return val(p);
	}
	inline void pop(reg int p){
		del(p)=true;
		fa(lson(p))=lson(p),fa(rson(p))=rson(p);
		fa(p)=merge(lson(p),rson(p));
		return;
	}
	inline int find(reg int p){
		if(p==fa(p))
			return p;
		else
			return fa(p)=find(fa(p));
	}
}

int n,m;
int rt[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		rt[i]=Heap::New(read());
	while(m--){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read();
				if(!Heap::del(x)&&!Heap::del(y)){
					reg int rx=Heap::find(x),ry=Heap::find(y);
					if(rx!=ry)
						Heap::fa(rx)=Heap::fa(ry)=Heap::merge(rx,ry);
				}
				break;
			}
			case 2:{
				x=read();
				if(!Heap::del(x)){
					reg int rx=Heap::find(x);
					writeln(Heap::top(rx));
					Heap::pop(rx);
				}
				else
					writeln(-1);
				break;
			}
		}
	}
	flush();
	return 0;
}