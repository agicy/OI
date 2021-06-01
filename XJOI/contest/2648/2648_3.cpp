#pragma GCC optimize("Ofast")
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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e5+5;

struct Node{
	ll s;
	int t;
	inline bool operator<(const Node& a)const{
		return t<a.t;
	}
	inline ll getVal(reg int tim)const{
		return s+1ll*(tim-1)*t;
	}
};

namespace FHQTreap{
	const int MAXSIZE=MAXN;
	struct Node{
		int lson,rson,siz;
		ll val,tAdd;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define tAdd(x) unit[(x)].tAdd
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg ll v){
		reg int p=++tot;
		lson(p)=rson(p)=0,siz(p)=1;
		val(p)=v,tAdd(p)=0;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void add(reg int p,reg ll v){
		val(p)+=v;
		tAdd(p)+=v;
		return;
	}
	inline void pushdown(reg int p){
		if(tAdd(p)){
			if(lson(p))
				add(lson(p),tAdd(p));
			if(rson(p))
				add(rson(p),tAdd(p));
			tAdd(p)=0;
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		pushdown(x),pushdown(y);
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
	inline int find(reg int p,const ::Node& a){
		reg int res=0;
		while(p){
			pushdown(p);
			reg ll v=a.getVal(res+siz(lson(p))+1);
			if(v<val(p)){
				res+=siz(lson(p))+1;
				p=rson(p);
			}
			else if(v==val(p))
				return res+siz(lson(p))+1;
			else
				p=lson(p);
		}
		return res;
	}
	ll ans=0;
	inline void print(reg int p){
		pushdown(p);
		if(lson(p))
			print(lson(p));
		ans+=val(p);
		writeln(ans);
		if(rson(p))
			print(rson(p));
		return;
	}
}

int n;
Node a[MAXN];

bool ed;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].s=readll(),a[i].t=read();
	sort(a+1,a+n+1);
	reg int rt=0;
	for(reg int i=1;i<=n;++i){
		reg int tim=FHQTreap::find(rt,a[i]);
		static int rt1,rt2;
		FHQTreap::split(rt,tim,rt1,rt2);
		FHQTreap::add(rt2,a[i].t);
		rt=FHQTreap::merge(FHQTreap::merge(rt1,FHQTreap::New(a[i].s+1ll*tim*a[i].t)),rt2);
	}
	FHQTreap::print(rt);
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}