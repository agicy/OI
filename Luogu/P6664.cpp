#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
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
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=3e5+5;
const int inf=0x3f3f3f3f;

int n,m;
int T[MAXM],L[MAXM],U[MAXM],V[MAXM];

namespace LCT{
	const int MAXSIZE=MAXN+MAXM;
	struct Node{
		int fa,ch[2];
		bool tRev;
		int id,Minid,sum;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define tRev(x) unit[(x)].tRev
		#define Minid(x) unit[(x)].Minid
		#define id(x) unit[(x)].id
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXSIZE];
	inline void New(reg int p,reg int v){
		fa(p)=lson(p)=rson(p)=0;
		tRev(p)=false;
		Minid(p)=id(p)=v;
		sum(p)=0;
		return;
	}
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline void pushup(reg int p){
		Minid(p)=id(p);
		if(lson(p)&&T[Minid(lson(p))]<T[Minid(p)])
			Minid(p)=Minid(lson(p));
		if(rson(p)&&T[Minid(rson(p))]<T[Minid(p)])
			Minid(p)=Minid(rson(p));
		sum(p)=sum(lson(p))+sum(rson(p))+L[id(p)];
		return;
	}
	inline void rotate(reg int p){
		if(isRoot(p))
			return;
		reg int f=fa(p),ff=fa(f),dir=get(p);
		if(!isRoot(f)) ch(ff)[get(f)]=p;
		if(ch(p)[dir^1]) fa(ch(p)[dir^1])=f;
		ch(f)[dir]=ch(p)[dir^1];
		ch(p)[dir^1]=f,fa(f)=p;
		fa(p)=ff;
		pushup(f),pushup(p);
		return;
	}
	inline void pushdown(reg int p){
		if(tRev(p)){
			swap(lson(p),rson(p));
			if(lson(p))
				tRev(lson(p))=!tRev(lson(p));
			if(rson(p))
				tRev(rson(p))=!tRev(rson(p));
			tRev(p)=false;
		}
		return;
	}
	inline void update(reg int p){
		if(!isRoot(p))
			update(fa(p));
		pushdown(p);
		return;
	}
	inline void splay(reg int p){
		update(p);
		for(reg int f;f=fa(p),!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		pushup(p);
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa(p))
			splay(p),rson(p)=pre,pushup(p);
		return;
	}
	inline void makeRoot(reg int p){
		access(p),splay(p),tRev(p)=!tRev(p);
		return;
	}
	inline void link(reg int x,reg int y){
		makeRoot(x),fa(x)=y;
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void cut(reg int x,reg int y){
		split(x,y);
		fa(x)=lson(y)=0;
		pushup(y);
		return;
	}
	inline int find(reg int p){
		access(p),splay(p);
		while(lson(p))
			pushdown(p),p=lson(p);
		return p;
	}
}

int main(void){
	n=read(),m=read();
	T[0]=inf;
	for(reg int i=1;i<=n+m;++i)
		LCT::New(i,i<=n?0:i-n);
	for(reg int i=1;i<=m;++i){
		static char opt;
		static int id,u,v,t,l;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'f':{
				id=read()+1,u=read()+1,v=read()+1,t=read(),l=read();
				T[id]=t,L[id]=l,U[id]=u,V[id]=v;
				if(LCT::find(u)==LCT::find(v)){
					LCT::split(u,v);
					reg int xid=LCT::Minid(v);
					if(T[xid]<T[id]){
						LCT::cut(u,xid+n),LCT::cut(v,xid+n);
						LCT::link(u,id+n),LCT::link(v,id+n);
					}
				}
				else
					LCT::link(u,id+n),LCT::link(v,id+n);
				break;
			}
			case 'm':{
				u=read()+1,v=read()+1;
				if(LCT::find(u)!=LCT::find(v))
					writeln(-1);
				else{
					LCT::split(u,v);
					writeln(LCT::sum(v));
				}
				break;
			}
			case 'c':{
				id=read()+1,l=read();
				LCT::splay(id+n);
				L[id]=l;
				LCT::pushup(id+n);
				break;
			}
		}
	}
	flush();
	return 0;
}