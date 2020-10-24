#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

int n,q;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int top[MAXN];
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	rnk[tim]=u;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

set<int> S[MAXN];
int c[MAXN];

inline int query(reg int u){
	int res=inf;
	while(top[u]!=1){
		reg int topf=top[u];
		if(!S[topf].empty()&&*S[topf].begin()<=dfn[u])
			cMin(res,*S[topf].begin());
		u=fa[topf];
	}
	if(!S[1].empty()&&*S[1].begin()<=dfn[u])
		cMin(res,*S[1].begin());
	return res;
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	while(q--){
		static int opt,v;
		opt=read(),v=read();
		switch(opt){
			case 0:{
				if(c[v])
					S[top[v]].erase(dfn[v]);
				else
					S[top[v]].insert(dfn[v]);
				c[v]^=1;
				break;
			}
			case 1:{
				reg int ans=query(v);
				printf("%d\n",ans==inf?-1:rnk[ans]);
				break;
			}
		}
	}
	return 0;
}