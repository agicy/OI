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

const int MAXN=1e5+5;
const int MAXM=3e5+5;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;

int n,m;
int val[MAXN];
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
int scc_cnt,col[MAXN],Min[MAXN],siz[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		reg int v;
		Min[scc_cnt]=inf;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
			Min[scc_cnt]=min(Min[scc_cnt],val[v]);
		}while(v!=u);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		val[i]=read();
	m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(val[i]==Min[col[i]])
			++siz[col[i]];
	reg ll ans1=0;
	reg int ans2=1;
	for(reg int i=1;i<=scc_cnt;++i)
		ans1+=Min[i],ans2=1ll*ans2*siz[i]%mod;
	printf("%lld %d\n",ans1,ans2);
	return 0;
}