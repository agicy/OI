#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXT=1e5+5;
const int MAXK=2e4;

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
	int scc_cnt,col[MAXN];
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
			reg int v;
			++scc_cnt;
			do{
				v=S[top--];
				vis[v]=false;
				col[v]=scc_cnt;
			}while(v!=u);
		}
		return;
	}
}

namespace DAG{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	int inDeg[MAXN];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

int n,m,t;
int a[MAXM],b[MAXM];
int qa[MAXT],qb[MAXT];
int in[MAXN];
bitset<MAXK+1> f[MAXN];

inline bool check(reg int l,reg int r){
	for(reg int i=1;i<=Graph::scc_cnt;++i){
		in[i]=DAG::inDeg[i];
		f[i].reset();
		if(l<=i&&i<=r)
			f[i][i-l]=true;
	}
	static int Q[MAXN];
	reg int head=0,tail=0;
	for(reg int i=1;i<=Graph::scc_cnt;++i)
		if(!in[i])
			Q[tail++]=i;
	while(head<tail){
		reg int u=Q[head++];
		for(reg int i=DAG::head[u];i;i=DAG::Next[i]){
			reg int v=DAG::to[i];
			f[v]|=f[u];
			--in[v];
			if(!in[v])
				Q[tail++]=v;
		}
	}
	using Graph::col;
	for(reg int i=1;i<=t;++i)
		if(l<=col[qb[i]]&&col[qb[i]]<=r&&f[col[qa[i]]][col[qb[i]]-l])
			return false;
	return true;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read();
		Graph::Add_Edge(a[i],b[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i);
	for(reg int i=1,u,v;i<=n;++i){
		u=Graph::col[a[i]],v=Graph::col[b[i]];
		if(u!=v){
			++DAG::inDeg[u];
			DAG::Add_Edge(v,u);
		}
	}
	t=read();
	for(reg int i=1;i<=t;++i)
		qa[i]=read(),qb[i]=read();
	for(reg int i=1,l,r;i<=Graph::scc_cnt;i+=MAXK){
		l=i,r=min(i+MAXK-1,Graph::scc_cnt);
		if(!check(l,r)){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	printf("%d\n",m);
	for(reg int i=1;i<=m;++i)
		printf("%d %d\n",a[i],b[i]);
	return 0;
}