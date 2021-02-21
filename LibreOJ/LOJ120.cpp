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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;

namespace FHQTreap{
	const int MAXSIZE=MAXN*150;
	struct Node{
		int ch[2];
		int siz;
		int val;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int v){
		reg int p=++tot;
		lson(p)=rson(p)=0;
		siz(p)=1;
		val(p)=v;
		return p;
	}
	inline int copy(reg int p){
		reg int q=++tot;
		unit[q]=unit[p];
		return q;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void split(reg int p,reg int k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
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
		if(rand()%(siz(x)+siz(y))<siz(x)){
			x=copy(x);
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			y=copy(y);
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
}

using namespace FHQTreap;

int n;
int rt[MAXN];

int main(void){
	n=read();
	reg int tot=0;
	while(n--){
		static int opt,t,k,x;
		opt=read();
		switch(opt){
			case 1:{
				t=read(),k=read(),x=read();
				static int rt1,rt2;
				split(rt[t],k-1,rt1,rt2);
				rt[++tot]=merge(merge(rt1,New(x)),rt2);
				break;
			}
			case 2:{
				t=read(),k=read();
				static int rt1,mid,rt2;
				split(rt[t],k-1,rt1,rt2);
				split(rt2,1,mid,rt2);
				rt[++tot]=merge(rt1,rt2);
				break;
			}
			case 3:{
				t=read(),k=read();
				writeln(kth(rt[t],k));
				break;
			}
		}
	}
	flush();
	return 0;
}