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
const int MAXM=2e5+5;
const int MAXQ=1e5+5;

int n,m,q;
int x[MAXM],y[MAXM];
int cnt=1,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,dfn[MAXN],low[MAXN];
bool cut[MAXM<<1];

inline void tarjan(reg int u,reg int id){
	dfn[u]=low[u]=++tim;
	for(reg int i=head[u];i;i=Next[i]){
		if(i==id)
			continue;
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,i^1);
			cMin(low[u],low[v]);
			if(low[v]>dfn[u])
				cut[i]=cut[i^1]=true;
		}
		else
			cMin(low[u],dfn[v]);
	}
	return;
}

int eDcc_cnt,col[MAXN];

inline void dfs(reg int u,reg int id){
	col[u]=id;
	for(reg int i=head[u];i;i=Next[i]){
		if(cut[i])
			continue;
		reg int v=to[i];
		if(!col[v])
			dfs(v,id);
	}
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

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
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

inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		x[i]=read(),y[i]=read();
		Add_Edge(x[i],y[i]);
		Add_Edge(y[i],x[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i,0);
	for(reg int i=1;i<=n;++i)
		if(!col[i]){
			++eDcc_cnt;
			dfs(i,eDcc_cnt);
		}
	cnt=0,memset(head,0,sizeof(head));
	for(reg int i=1;i<=m;++i)
		if(col[x[i]]!=col[y[i]]){
			Add_Edge(col[x[i]],col[y[i]]);
			Add_Edge(col[y[i]],col[x[i]]);
		}
	dfs1(1,0);
	dfs2(1,0,1);
	q=read();
	while(q--){
		static int a,b;
		a=read(),b=read();
		reg int x=col[a],y=col[b];
		reg int lca=LCA(x,y);
		printf("%d\n",dep[x]+dep[y]-dep[lca]*2);
	}
	return 0;
}