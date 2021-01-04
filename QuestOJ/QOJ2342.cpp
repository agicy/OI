#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;

int n,m,q;

namespace Graph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

namespace DAG{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

int tim,dfn[MAXM],low[MAXM];
int top,S[MAXM];
int scc_cnt,col[MAXM];

inline void tarjan(reg int u){
	S[++top]=u;
	low[u]=dfn[u]=++tim;
	for(reg int i=Graph::head[u],v;i;i=Graph::Next[i]){
		v=Graph::to[i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
		}
		else if(!col[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		reg int v;
		do
			col[v=S[top--]]=scc_cnt;
		while(v!=u);
	}
	return;
}

int u[MAXM],v[MAXM];

struct querys{
	int id,u,v;
	inline bool operator<(const querys& a)const{
		return col[u]==col[a.u]?col[v]<col[a.v]:col[u]<col[a.u];
	}
};

querys Q[MAXQ];
bitset<MAXN> M,T;

inline bool dfs(reg int u,reg int t){
	reg bool f=false;
	for(reg int i=DAG::head[u],v;i;i=DAG::Next[i]){
		v=DAG::to[i];
		if(T[v])
			continue;
		T[v]=true;
		if(v==t){
			f=true;
			continue;
		}
		f|=dfs(v,t);
	}
	return f;
}

bool ans[MAXQ];

inline void Solve(void){
	reg int las=0;
	for(reg int i=1,x,y;i<=q;++i){
		x=col[Q[i].u],y=col[Q[i].v];
		if(x==y)
			ans[Q[i].id]=true;
		else{
			if(x!=las){
				T.reset();
				if(dfs(x,las))
					M|=T;
				else
					M=T;
				las=x;
			}
			if(M[y])
				ans[Q[i].id]=true;
		}
	}
	return;
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		Graph::Add_Edge(u[i],v[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1,x,y;i<=m;++i){
		x=col[u[i]],y=col[v[i]];
		if(x!=y)
			DAG::Add_Edge(x,y);
	}
	for(reg int i=1;i<=q;++i)
		Q[i].id=i,Q[i].u=read(),Q[i].v=read();
	sort(Q+1,Q+q+1);
	Solve();
	for(reg int i=1;i<=q;++i)
		putchar(ans[i]?'Y':'N');
	putchar('\n');
	flush();
	return 0;
}