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

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

inline void swap(reg int &a,reg int &b){
	a^=b,b=a^b,a^=b;
	return;
}

const int MAXN=3e5+5;
const int MAXM=3e5+5;

int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int n,m;
ll h[MAXN];
bool a[MAXN];
ll v[MAXN];
int c[MAXM];
int rt[MAXN];
int ans1[MAXN],ans2[MAXM];

namespace Heap{
	struct Node{
		int lson,rson,dis;
		ll val,tAdd,tMul;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define dis(x) unit[(x)].dis
		#define val(x) unit[(x)].val
		#define tAdd(x) unit[(x)].tAdd
		#define tMul(x) unit[(x)].tMul
	};
	Node unit[MAXM];
	inline void Add(reg int p,reg ll v){
		val(p)+=v,tAdd(p)+=v;
		return;
	}
	inline void Mul(reg int p,reg ll v){
		val(p)*=v,tAdd(p)*=v,tMul(p)*=v;
		return;
	}
	inline void pushdown(reg int p){
		if(tMul(p)!=1){
			if(lson(p))
				Mul(lson(p),tMul(p));
			if(rson(p))
				Mul(rson(p),tMul(p));
			tMul(p)=1;
		}
		if(tAdd(p)){
			if(lson(p))
				Add(lson(p),tAdd(p));
			if(rson(p))
				Add(rson(p),tAdd(p));
			tAdd(p)=0;
		}
		return;
	}
	inline void pushup(reg int p){
		dis(p)=dis(rson(p))+1;
		return;
	}
	inline int merge(int x,int y){
		if(!x||!y)
			return x|y;
		if(val(x)>val(y))
			swap(x,y);
		pushdown(x);
		rson(x)=merge(rson(x),y);
		if(dis(lson(x))<dis(rson(x)))
			swap(lson(x),rson(x));
		pushup(x);
		return x;
	}
	inline ll top(reg int p){
		return val(p);
	}
	inline int pop(reg int p){
		pushdown(p);
		return merge(lson(p),rson(p));
	}
}

int dep[MAXN];

inline void dfs(reg int u,reg int father){
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v,u);
		rt[u]=Heap::merge(rt[u],rt[v]);
	}
	while(rt[u]&&Heap::top(rt[u])<h[u]){
		++ans1[u];
		ans2[rt[u]]=dep[c[rt[u]]]-dep[u];
		rt[u]=Heap::pop(rt[u]);
	}
	if(a[u])
		Heap::Mul(rt[u],v[u]);
	else
		Heap::Add(rt[u],v[u]);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		h[i]=readll();
	for(reg int i=2;i<=n;++i){
		static int f;
		f=read(),a[i]=read(),v[i]=readll();
		Add_Edge(f,i);
	}
	for(reg int i=1;i<=m;++i){
		static ll s;
		s=readll(),c[i]=read();
		Heap::val(i)=s,Heap::tMul(i)=1;
		rt[c[i]]=Heap::merge(rt[c[i]],i);
	}
	dfs(1,0);
	while(rt[1]){
		ans2[rt[1]]=dep[c[rt[1]]];
		rt[1]=Heap::pop(rt[1]);
	}
	for(reg int i=1;i<=n;++i)
		writeln(ans1[i]);
	for(reg int i=1;i<=m;++i)
		writeln(ans2[i]);
	flush();
	return 0;
}