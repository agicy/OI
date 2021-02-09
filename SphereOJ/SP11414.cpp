#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

int n;
int c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int rt[MAXN];

namespace Trie{
	const int MAXSIZE=MAXN*50;
	struct Node{
		int ch[2];
		int cov,tag;
		#define ch(x) unit[(x)].ch
		#define cov(x) unit[(x)].cov
		#define tag(x) unit[(x)].tag
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int p){
		cov(p)=cov(lson(p))&&cov(rson(p));
		return;
	}
	inline void insert(reg int &p,reg int val,reg int dep){
		p=++tot;
		if(dep==-1){
			cov(p)=true;
			return;
		}
		insert(ch(p)[(val>>dep)&1],val,dep-1);
		pushup(p);
		return;
	}
	inline void Xor(reg int p,reg int val,reg int dep){
		if(dep<0)
			return;
		if((val>>dep)&1)
			swap(lson(p),rson(p));
		tag(p)^=val;
		return;
	}
	inline void pushdown(reg int p,reg int dep){
		if(tag(p)){
			if(lson(p))
				Xor(lson(p),tag(p),dep-1);
			if(rson(p))
				Xor(rson(p),tag(p),dep-1);
			tag(p)=0;
		}
		return;
	}
	inline int merge(reg int x,reg int y,reg int dep){
		if(!x||!y)
			return x|y;
		if(dep==-1)
			cov(x)|=cov(y);
		else{
			pushdown(x,dep),pushdown(y,dep);
			lson(x)=merge(lson(x),lson(y),dep-1);
			rson(x)=merge(rson(x),rson(y),dep-1);
			pushup(x);
		}
		return x;
	}
	inline int getMex(reg int p,reg int dep){
		if(!p||dep==-1)
			return 0;
		pushdown(p,dep);
		if(cov(lson(p)))
			return getMex(rson(p),dep-1)^(1<<dep);
		else
			return getMex(lson(p),dep-1);
	}
}

int sg[MAXN];

inline void dfs1(reg int u,reg int father){
	reg int Xor=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			Xor^=sg[v];
		}
	}
	if(!c[u])
		Trie::insert(rt[u],Xor,MAXLOG2N-1);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			Trie::Xor(rt[v],Xor^sg[v],MAXLOG2N-1);
			rt[u]=Trie::merge(rt[u],rt[v],MAXLOG2N-1);
		}
	}
	sg[u]=Trie::getMex(rt[u],MAXLOG2N-1);
	return;
}

int tot,ans[MAXN];

inline void dfs2(reg int u,reg int father,reg int Xor){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			Xor^=sg[v];
	}
	if(!c[u]&&!Xor)
		ans[++tot]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs2(v,u,Xor^sg[v]);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0);
	if(!sg[1])
		puts("-1");
	else{
		tot=0;
		dfs2(1,0,0);
		sort(ans+1,ans+tot+1);
		for(reg int i=1;i<=tot;++i)
			printf("%d\n",ans[i]);
	}
	return 0;
}