#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;

int n;
vector<int> G[MAXN];
int fa[MAXN],dep[MAXN];

inline void dfs1(reg int u,reg int father){
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int v:G[u])
		if(v!=father)
			dfs1(v,u);
	return;
}

bool tag[MAXN];
int tim,dfn[MAXN];

inline void dfs2(reg int u,reg int father){
	dfn[u]=++tim;
	reg int son=0;
	for(int v:G[u])
		if(v!=father){
			if(!tag[v])
				dfs2(v,u);
			else
				son=v;
		}
	if(son)
		dfs2(son,u);
	++tim;
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	dfs1(1,0);
	reg int rt=1;
	for(reg int i=2;i<=n;++i)
		if(dep[i]>=dep[rt])
			rt=i;
	dfs1(rt,0);
	reg int ptr=1;
	for(reg int i=2;i<=n;++i)
		if(dep[i]>=dep[ptr])
			ptr=i;
	while(ptr)
		tag[ptr]=true,ptr=fa[ptr];
	dfs2(rt,0);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",dfn[i],i==n?'\n':' ');
	return 0;
}