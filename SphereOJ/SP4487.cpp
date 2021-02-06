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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int inf=0x3f3f3f3f;

namespace FHQTreap{
	const int MAXSIZE=MAXN+MAXM;
	struct Node{
		int ch[2],siz;
		int val;
		int sum,lMax,rMax,Max;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define Max(x) unit[(x)].Max
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
		Max(p)=max(max(Max(lson(p)),Max(rson(p))),rMax(lson(p))+val(p)+lMax(rson(p)));
		lMax(p)=max(lMax(lson(p)),sum(lson(p))+val(p)+lMax(rson(p)));
		rMax(p)=max(rMax(rson(p)),sum(rson(p))+val(p)+rMax(lson(p)));
		return;
	}
	inline int New(reg int v){
		reg int p=++tot;
		siz(p)=1;
		lMax(p)=rMax(p)=max(v,0);
		sum(p)=Max(p)=val(p)=v;
		return p;
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
}

int n,m,rt;

int main(void){
	srand(time(0));
	n=read();
	using namespace FHQTreap;
	for(reg int i=1;i<=n;++i){
		static int val;
		val=read();
		rt=merge(rt,New(val));
	}
	Max(0)=-inf;
	reg int m=read();
	while(m--){
		static char opt;
		static int p,x,l,r,rt1,rt2,mid;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'I':{
				p=read(),x=read();
				split(rt,p-1,rt1,rt2);
				rt=merge(merge(rt1,New(x)),rt2);
				break;
			}
			case 'D':{
				p=read();
				split(rt,p-1,rt1,rt2);
				split(rt2,1,mid,rt2);
				rt=merge(rt1,rt2);
				break;
			}
			case 'R':{
				p=read(),x=read();
				split(rt,p-1,rt1,rt2);
				split(rt2,1,mid,rt2);
				val(mid)=x;
				pushup(mid);
				rt=merge(merge(rt1,mid),rt2);
				break;
			}
			case 'Q':{
				l=read(),r=read();
				split(rt,r,rt1,rt2);
				split(rt1,l-1,rt1,mid);
				writeln(Max(mid));
				rt=merge(merge(rt1,mid),rt2);
				break;
			}
		}
	}
	flush();
	return 0;
}