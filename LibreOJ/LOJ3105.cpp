#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

const int MAXN=1e6+5;
const int inf=0x3f3f3f3f;

inline uint randNum(reg uint &seed,reg uint last,reg uint m){
	seed=seed*17+last;
	return seed%m+1;
}

int rt;

namespace Splay{
	struct Node{
		int fa,ch[2];
		int siz,cnt;
		pair<int,int> val;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define cnt(x) unit[(x)].cnt
		#define val(x) unit[(x)].val
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	int tot;
	Node unit[MAXN];
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+cnt(p);
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
	inline void splay(reg int x,reg int goal){
		for(reg int f;f=fa(x),f!=goal;rotate(x))
			if(fa(f)!=goal)
				rotate(get(x)==get(f)?f:x);
		if(!goal)
			rt=x;
		return;
	}
	inline int pre(const pair<int,int>& v){
		reg int p=rt,las;
		while(p)
			if(val(p)<v)
				las=p,p=rson(p);
			else
				p=lson(p);
		return las;
	}
	inline int nxt(const pair<int,int>& v){
		reg int p=rt,las;
		while(p)
			if(val(p)>v)
				las=p,p=lson(p);
			else
				p=rson(p);
		return las;
	}
	int top,S[MAXN];
	inline void del(const pair<int,int>& v){
		reg int x=pre(v),y=nxt(v);
		splay(x,0),splay(y,x);
		reg int p=lson(y);
		if(cnt(p)>1)
			--cnt(p),splay(p,0);
		else
			S[++top]=p,fa(p)=0,lson(y)=0,pushup(y),pushup(x);
		return;
	}
	inline int getId(void){
		if(top)
			return S[top--];
		else
			return ++tot;
	}
	inline int New(const pair<int,int>& v){
		reg int p=getId();
		fa(p)=lson(p)=rson(p)=0;
		siz(p)=cnt(p)=1;
		val(p)=v;
		return p;
	}
	inline void insert(const pair<int,int>& v){
		reg int p=rt,las=0;
		while(p&&val(p)!=v)
			las=p,p=ch(p)[val(p)<v];
		if(p)
			++cnt(p);
		else{
			p=New(v);
			if(las)
				fa(p)=las,ch(las)[val(las)<v]=p;
		}
		splay(p,0);
		return;
	}
}

int n;
int a[MAXN],b[MAXN];
uint m,seed;

int main(void){
	reg uint lastans=7;
	reg int T=read();
	while(T--){
		m=read(),n=read(),seed=read();
		rt=Splay::tot=Splay::top=0;
		Splay::insert(make_pair(inf,-inf)),Splay::insert(make_pair(-inf,inf));
		memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
		for(reg int i=1,Ria,Rib;i<=n;++i){
			Ria=randNum(seed,lastans,m),Rib=randNum(seed,lastans,m);
			if(a[Ria]) Splay::del(make_pair(a[Ria],-b[Ria]));
			++a[Ria],b[Ria]+=Rib;
			Splay::insert(make_pair(a[Ria],-b[Ria]));
			writeln(lastans=Splay::siz(Splay::rson(rt))-1);
		}
	}
	flush();
	return 0;
}