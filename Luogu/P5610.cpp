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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
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

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

const int MAXN=1e5+5;
const int MAXA=5e5+5;
const int MAXS=1e7+5;

int n,m;
int a[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int __buf[MAXA*400],*ptr=__buf;

struct UnionFind{
	int *fa;
	inline void init(reg int n){
		for(reg int i=0;i<n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
};

UnionFind U[MAXA];
int *pos[MAXA];
int cnt[MAXA];
int dcnt[MAXA];

namespace Graph{
	int cnt,head[MAXA],to[MAXS],nxt[MAXS];
	inline void Add_Edge(reg int u,reg int v){
		nxt[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

inline void update(reg int l,reg int r,reg int d){
	if(d!=1){
		reg int lef=lower_bound(pos[d],pos[d]+cnt[d],l)-pos[d],rig=upper_bound(pos[d],pos[d]+cnt[d],r)-pos[d]-1;
		if(lef>rig)
			return;
		for(reg int u=U[d].find(lef);u<=rig;u=U[d].find(u+1)){
			reg int p=pos[d][u];
			if(!(a[p]%d))
				BIT::update(p,a[p]/d-a[p]),a[p]/=d;
			if(u>=rig)
				break;
			if(a[p]%d)
				U[d].fa[u]=U[d].find(u+1);
		}
	}
	return;
}

inline ll query(reg int l,reg int r){
	return BIT::query(r)-BIT::query(l-1);
}

int main(void){
	n=read(),m=read();
	reg int Max=0;
	BIT::init(n);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		++cnt[a[i]];
		Max=max(Max,a[i]);
		BIT::update(i,a[i]);
	}
	for(reg int i=1;i<=Max;++i){
		for(reg int j=i;j<=Max;j+=i)
			if(cnt[j]){
				dcnt[i]+=cnt[j];
				Graph::Add_Edge(j,i);
			}
		cnt[i]=0;
	}
	for(reg int i=1;i<=Max;++i)
		if(dcnt[i]){
			pos[i]=ptr;
			ptr+=dcnt[i];
			U[i].fa=ptr;
			ptr+=dcnt[i];
			U[i].init(dcnt[i]);
			dcnt[i]=0;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=Graph::head[a[i]];j;j=Graph::nxt[j])
			pos[Graph::to[j]][cnt[Graph::to[j]]++]=i;
	reg ll lastans=0;
	while(m--){
		static int opt;
		static ll l,r;
		opt=read(),l=readll()^lastans,r=readll()^lastans;
		switch(opt){
			case 1:{
				update(l,r,readll()^lastans);
				break;
			}
			case 2:{
				writeln(lastans=query(l,r));
				break;
			}
		}
	}
	flush();
	return 0;
}