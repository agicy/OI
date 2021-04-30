#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=1e3+5;
const int MAXM=2e5+5;

struct Edge{
	int u,v;
	inline Edge(reg int u=0,reg int v=0):u(u),v(v){
		return;
	}
};

int n,m;
Edge E[MAXM];
vector<int> G[MAXN];
int tag[MAXN];
bool vis[MAXN];
bool ans[2][MAXN][MAXN];

inline void dfs1(reg int u,reg int s){
	vis[u]=true;
	ans[0][s][u]=true;
	for(int v:G[u])
		if(!vis[v])
			dfs1(v,s);
	return;
}

inline void dfs2(reg int u,reg int col,reg bool k,reg int s){
	vis[u]=true;
	if(k)
		ans[1][s][u]=(tag[u]!=col);
	else
		tag[u]=col;
	for(int v:G[u])
		if(!vis[v])
			dfs2(v,col,k,s);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		E[i].u=read(),E[i].v=read();
		G[E[i].u].push_back(E[i].v);
	}
	for(reg int i=1;i<=n;++i){
		fill(vis+1,vis+n+1,false);
		dfs1(i,i);
	}
	for(reg int i=1;i<=n;++i){
		memset(tag,0,sizeof(tag));
		fill(vis+1,vis+n+1,false),vis[i]=true;
		for(reg int j=0,siz=G[i].size();j<siz;++j){
			reg int v=G[i][j];
			if(!vis[v])
				dfs2(v,j+1,0,i);
		}
		fill(vis+1,vis+n+1,false),vis[i]=true;
		for(reg int j=G[i].size()-1;j>=0;--j){
			reg int v=G[i][j];
				if(!vis[v])
					dfs2(v,j+1,1,i);
		}
	}
	for(reg int i=1;i<=m;++i)
		writeln(ans[0][E[i].v][E[i].u]^ans[1][E[i].u][E[i].v]?"diff":"same");
	flush();
	return 0;
}