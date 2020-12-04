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

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e4+5;
const int MAXM=1e5+5;

int n,m;
int c[MAXN];
int u[MAXM],v[MAXM];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int scc_cnt,col[MAXN],siz[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		reg int v;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
			siz[scc_cnt]+=c[v];
		}while(v!=u);
	}
	return;
}

int indeg[MAXN];
int f[MAXN];
queue<int> Q;

inline int topo(void){
	for(int i=1;i<=scc_cnt;++i)
		if(!indeg[i]){
			f[i]=siz[i];
			Q.push(i);
		}
	int res=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		res=max(res,f[u]);
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			--indeg[v];
			f[v]=max(f[v],f[u]+siz[v]);
			if(!indeg[v])
				Q.push(v);
		}
	}
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		Add_Edge(u[i],v[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	cnt=0,memset(head,0,sizeof(head));
	for(reg int i=1;i<=m;++i)
		if(col[u[i]]!=col[v[i]]){
			Add_Edge(col[u[i]],col[v[i]]);
			++indeg[col[v[i]]];
		}
	printf("%d\n",topo());
	return 0;
}