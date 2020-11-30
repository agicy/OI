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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMax(reg int& a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int& a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e3+5;
const int MAXM=1e3+5;
const int MAXV=MAXN*MAXM;
const int MAXE=MAXV*4;

int n,m;
int id[MAXN][MAXM];
int h[MAXV],V[MAXV];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int scc_cnt,col[MAXV],siz[MAXV];
ll sum[MAXV];

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
			sum[scc_cnt]+=V[v];
			++siz[scc_cnt];
		}while(u!=v);
	}
	return;
}

namespace DAG{
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	int indeg[MAXV];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

ll f[MAXV];
queue<int> Q;

int main(void){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);

	n=read(),m=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			id[i][j]=++tot;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			h[id[i][j]]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			V[id[i][j]]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			const int dx[]={-1,0,0,1};
			const int dy[]={0,-1,1,0};
			for(reg int k=0;k<4;++k){
				reg int fx=i+dx[k],fy=j+dy[k];
				if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&h[id[i][j]]>=h[id[fx][fy]])
					Add_Edge(id[i][j],id[fx][fy]);
			}
		}
	for(reg int i=1;i<=tot;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=tot;++i)
		for(reg int j=head[i];j;j=Next[j]){
			reg int v=to[j];
			if(col[i]!=col[v]){
				++DAG::indeg[col[v]];
				DAG::Add_Edge(col[i],col[v]);
			}
		}
	for(int i=1;i<=scc_cnt;++i)
		if(!DAG::indeg[i]){
			if(siz[i]==1)
				f[i]=sum[i];
			else
				f[i]=(sum[i]<<1);
			Q.push(i);
		}
	ll ans=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		ans=max(ans,f[u]);
		for(reg int i=DAG::head[u];i;i=DAG::Next[i]){
			int v=DAG::to[i];
			--DAG::indeg[v];
			if(siz[v]==1)
				f[v]=max(f[v],f[u]+sum[v]);
			else
				f[v]=max(f[v],f[u]+(sum[v]<<1));
			if(!DAG::indeg[v])
				Q.push(v);
		}
	}
	printf("%lld\n",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}