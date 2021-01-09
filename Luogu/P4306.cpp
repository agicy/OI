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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

const int MAXN=2e3+5;
const int MAXM=MAXN*MAXN;

namespace Graph{
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
				++siz[scc_cnt];
				col[v]=scc_cnt;
			}while(v!=u);
		}
		return;
	}
}

namespace DAG{
	int indeg[MAXN];
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		++indeg[v];
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

int n;
char M[MAXN][MAXN];
bitset<MAXN> f[MAXN];
int Q[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		read(M[i]+1);
		for(reg int j=1;j<=n;++j)
			if(M[i][j]=='1')
				Graph::Add_Edge(j,i);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if((M[i][j]^'0')&&Graph::col[i]!=Graph::col[j])
				DAG::Add_Edge(Graph::col[j],Graph::col[i]);
	reg int head_=0,tail_=0;
	for(reg int i=1;i<=Graph::scc_cnt;++i){
		if(!DAG::indeg[i])
			Q[tail_++]=i;
		f[i][i]=true;
	}
	while(head_<tail_){
		reg int u=Q[head_++];
		for(reg int i=DAG::head[u];i;i=DAG::Next[i]){
			reg int v=DAG::to[i];
			f[v]|=f[u];
			--DAG::indeg[v];
			if(!DAG::indeg[v])
				Q[tail_++]=v;
		}
	}
	reg int ans=0;
	for(reg int i=1;i<=Graph::scc_cnt;++i)
		for(reg int j=1;j<=Graph::scc_cnt;++j)
			if(f[i][j])
				ans+=Graph::siz[i]*Graph::siz[j];
	printf("%d\n",ans);
	return 0;
}