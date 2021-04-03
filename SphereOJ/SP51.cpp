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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e3+5;

int n;
vector<int> G[MAXN];
bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int scc_cnt,col[MAXN],siz[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=0,siz=G[u].size();i<siz;++i){
		reg int v=G[u][i];
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
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
			++siz[scc_cnt];
		}while(v!=u);
	}
	return;
}

bool tag[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			G[i].clear();
		for(int i=1;i<=n;++i){
			reg int s=read();
			for(reg int j=0;j<s;++j)
				G[read()].push_back(i);
		}
		tim=0,fill(dfn+1,dfn+n+1,0);
		scc_cnt=0,fill(siz+1,siz+n+1,0);
		for(reg int i=1;i<=n;++i)
			if(!dfn[i])
				tarjan(i);
		fill(tag+1,tag+scc_cnt+1,false);
		for(reg int i=1;i<=n;++i)
			for(reg int j=0,siz=G[i].size();j<siz;++j)
				if(col[i]!=col[G[i][j]])
					tag[col[G[i][j]]]=true;
		reg int cnt=0,ans=0;
		for(reg int i=1;i<=scc_cnt;++i)
			if(!tag[i])
				++cnt,ans+=siz[i];
		writeln(cnt>1?0:ans);
	}
	flush();
	return 0;
}