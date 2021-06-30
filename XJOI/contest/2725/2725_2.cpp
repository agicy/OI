#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

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
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int inf=0x3f3f3f3f;

namespace Splay{
	struct Node{
		int fa,ch[2],siz;
		int val,Max;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define Max(x) unit[(x)].Max
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXN+MAXQ];
	inline void init(void){
		Max(0)=-inf;
		return;
	}
	inline bool get(reg int p){
		return p==rson(fa(p));
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		Max(p)=max(max(Max(lson(p)),Max(rson(p))),val(p));
		return;
	}
	inline void rotate(reg int p){
		reg int f=fa(p),ff=fa(f),dir=get(p);
		ch(f)[dir]=ch(p)[dir^1];
		fa(ch(f)[dir])=f;
		ch(p)[dir^1]=f,fa(f)=p,fa(p)=ff;
		if(ff) ch(ff)[rson(ff)==f]=p;
		pushup(f),pushup(p);
		return;
	}
	inline void splay(reg int x){
		for(reg int f;f=fa(x),f;rotate(x))
			if(fa(f))
				rotate(get(x)==get(f)?f:x);
		return;
	}
	inline void setVal(reg int id,reg int v){
		splay(id);
		val(id)=v;
		pushup(id);
		return;
	}
	inline int getMax(reg int p){
		while(true){
			if(Max(p)==val(p))
				return p;
			else if(Max(p)==Max(lson(p)))
				p=lson(p);
			else
				p=rson(p);
		}
		return -1;
	}
	#undef fa
	#undef ch
	#undef siz
	#undef val
	#undef Max
	#undef lson
	#undef rson
}

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
};

int n,q;

bool ed;

int main(void){
	n=read(),q=read();
	Splay::init();
	for(reg int i=1;i<=n;++i)
		Splay::setVal(i,read());
	reg int tot=n;
	while(q--){
		static int w,x,y,k;
		switch(read()){
			case 1:{
				w=read(),x=read(),y=read();
				Splay::splay(x),Splay::splay(y);
				++tot;
				Splay::unit[tot].ch[0]=x,Splay::unit[tot].ch[1]=y;
				Splay::unit[x].fa=Splay::unit[y].fa=tot;
				Splay::setVal(tot,w);
				break;
			}
			case 2:{
				x=read();
				Splay::splay(x);
				Splay::unit[Splay::unit[x].ch[0]].fa=Splay::unit[Splay::unit[x].ch[1]].fa=0;
				break;
			}
			case 3:{
				x=read(),k=read();
				Splay::splay(x);
				reg int top=0;
				static Node S[MAXN+MAXQ];
				--k;
				while(k--){
					Splay::splay(x);
					reg int p=Splay::getMax(x);
					S[++top]=Node(p,Splay::unit[p].val);
					Splay::setVal(p,-inf);
				}
				Splay::splay(x);
				writeln(Splay::unit[Splay::getMax(x)].val);
				while(top){
					Splay::setVal(S[top].id,S[top].val);
					--top;
				}
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}