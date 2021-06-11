#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e3+5;

int n,m,q;
vector<int> G[MAXN],invG[MAXN];
bool vis[2][MAXN][MAXN];
vector<int> D[MAXN];
int fa[MAXN];

inline void dfs1(reg int u,reg int del){
	vis[0][del][u]=true;
	if(u==del)
		return;
	for(int v:G[u])
		if(!vis[0][del][v])
			dfs1(v,del);
	return;
}

inline bool cmp(reg int a,reg int b){
	return D[a].size()<D[b].size();
}

inline void dfs2(reg int u,reg int tag,reg int del){
	if(u==del)
		return;
	vis[1][tag][u]=true;
	for(int v:invG[u])
		if(!vis[1][tag][v])
			dfs2(v,tag,del);
	return;
}

inline void swap(reg bool& a,reg bool& b){
	reg bool tmp=a;
	a=b;
	b=tmp;
	return;
}

inline void swap(reg bool G[MAXN][MAXN]){
	for(reg int i=1;i<=n;++i)
		for(reg int ptr=i+1;ptr<=n;++ptr)
			swap(G[i][ptr],G[ptr][i]);
	return;
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		G[x].push_back(y);
		invG[y].push_back(x);
	}
	dfs1(1,0);
	for(int i=1;i<=n;++i){
		dfs1(1,i);
		for(reg int j=1;j<=n;++j)
			if(!vis[0][i][j])
				D[j].push_back(i);
	}
	static int id[MAXN];
	for(reg int i=1;i<=n;++i)
		id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;++i){
		reg int u=id[i];
		for(int f:D[u])
			if(D[f].size()+1==D[u].size())
				fa[u]=f;
	}
	for(reg int i=2;i<=n;++i)
		dfs2(i,i,fa[i]);
	swap(vis[0]),swap(vis[1]);
	for(reg int i=1;i<=q;++i){
		static int s,t;
		s=read(),t=read();
		static bool ans[MAXN];
		for(reg int u=1;u<=n;++u)
			if(vis[0][s][fa[u]]&&vis[1][t][u]&&fa[u]!=1&&fa[u]!=s)
				ans[u]=true;
		for(reg int j=1;j<=n;++j){
			reg int u=id[j];
			if(ans[fa[u]])
				ans[u]=true;
		}
		reg int sum=0;
		for(reg int u=1;u<=n;++u)
			if(ans[u])
				ans[u]=false,++sum;
		writeln(sum);
	}
	flush();
	return 0;
}