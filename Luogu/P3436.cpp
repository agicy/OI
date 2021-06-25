#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e6+5;
const int MAXM=1e6+5;

int n,m;
vector<int> G[MAXN];

inline void Add_Edge(reg int u,int v){
	G[u].push_back(v);
	return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int scc_cnt,col[MAXN],siz[MAXN];
bool tag[MAXN];

inline void tarjan(reg int u){
	reg bool flag=false;
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(int v:G[u]){
		if(u==v){
			flag=true;
			continue;
		}
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		if(flag||S[top]!=u)
			tag[scc_cnt]=true;
		reg int v;
		do{
			v=S[top--];
			vis[v]=false;
			++siz[scc_cnt];
			col[v]=scc_cnt;
		}while(v!=u);
	}
	return;
}

int inDeg[MAXN];
int f[MAXN];
queue<int> Q;

inline void topo(void){
	f[col[n]]=1;
	for(reg int i=1;i<=scc_cnt;++i)
		if(!inDeg[i])
			Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		if(u==col[n])
			continue;
		for(int v:G[u]){
			--inDeg[v];
			if(!inDeg[v])
				Q.push(v);
		}
	}
	Q.push(col[n]);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		if(tag[u]&&f[u])
			f[u]=36501;
		for(int v:G[u]){
			f[v]=min(f[v]+f[u],36501);
			--inDeg[v];
			if(!inDeg[v])
				Q.push(v);
		}
	}
	return;
}

int u[MAXM],v[MAXM];

int main(void){
	n=read()+1,m=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		Add_Edge(v[i],u[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=scc_cnt;++i)
		G[i].clear();
	for(reg int i=1;i<=m;++i)
		if(col[u[i]]!=col[v[i]]){
			++inDeg[col[u[i]]];
			Add_Edge(col[v[i]],col[u[i]]);
		}
	topo();
	reg int ans=0;
	for(reg int i=1;i<=scc_cnt;++i)
		ans=max(ans,f[i]);
	if(ans==36501)
		puts("zawsze");
	else
		printf("%d\n",ans);
	reg int res=0;
	if(ans==f[col[n]])
		--res;
	for(reg int i=1;i<=scc_cnt;++i)
		if(ans==f[i])
			res+=siz[i];
	printf("%d\n",res);
	for(reg int i=1;i<n;++i)
		if(ans==f[col[i]])
			printf("%d ",i);
	putchar('\n');
	return 0;
}