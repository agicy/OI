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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;
const int K=2e4;

namespace Graph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	/*
	vector<int> G[MAXN];
	inline void Add_Edge(const int& u,const int& v){
		G[u].push_back(v);
		return;
	}
	*/
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
		/*
		for(int v:G[u])
			if(!dfn[v]){
				tarjan(v);
				cMin(low[u],low[v]);
			}
			else if(vis[v])
				cMin(low[u],dfn[v]);
		*/
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
	int indeg[MAXN];
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		++indeg[v];
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	/*
	vector<int> G[MAXN];
	inline void Add_Edge(const int& u,const int& v){
		G[u].push_back(v);
		++indeg[v];
		return;
	}
	*/
}

struct querys{
	int id,u;
	inline querys(reg int id=0,reg int u=0):id(id),u(u){
		return;
	}
};

int n,m,q;
int a[MAXM],b[MAXM];
int in[MAXN];
bitset<K+1> f[MAXN];
int Q[MAXN];
vector<querys> Qu[MAXN];
bool ans[MAXQ];

inline void check(reg int l,reg int r){
	for(reg int i=1;i<=Graph::scc_cnt;++i){
		in[i]=DAG::indeg[i];
		f[i].reset();
		if(l<=i&&i<=r)
			f[i][i-l]=true;
	}
	reg int h=0,t=0;
	for(reg int i=1;i<=Graph::scc_cnt;++i)
		if(!in[i])
			Q[t++]=i;
	while(h<t){
		reg int u=Q[h++];
		for(reg int i=DAG::head[u];i;i=DAG::Next[i]){
			reg int v=DAG::to[i];
			f[v]=f[v]|f[u];
			--in[v];
			if(!in[v])
				Q[t++]=v;
		}
		/*
		for(int v:DAG::G[u]){
			f[v]=f[v]|f[u];
			--in[v];
			if(!in[v])
				Q[t++]=v;
		}*/
	}
	using Graph::col;
	for(reg int i=l;i<=r;++i)
		for(querys q:Qu[i])
			ans[q.id]=f[q.u][i-l];
	return;
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read();
		Graph::Add_Edge(a[i],b[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i);
	for(reg int i=1,u,v;i<=m;++i){
		u=Graph::col[a[i]],v=Graph::col[b[i]];
		if(u!=v)
			DAG::Add_Edge(v,u);
	}
	for(reg int i=1;i<=q;++i){
		static int u,v;
		u=read(),v=read();
		Qu[Graph::col[v]].push_back(querys(i,Graph::col[u]));
	}
	for(reg int i=1,l,r;i<=Graph::scc_cnt;i+=K){
		l=i,r=min(i+K-1,Graph::scc_cnt);
		check(l,r);
	}
	for(reg int i=1;i<=q;++i)
		putchar(ans[i]?'Y':'N');
	putchar('\n');
	flush();
	return 0;
}