#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e3+5;
const int MAXM=6e5+5;

int n,m;
int u[MAXM],v[MAXM];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,dfn[MAXN],low[MAXN];
bool vis[MAXN];
int top,S[MAXN];
int scc_cnt,col[MAXN];

inline void tarjan(reg int u){
	dfn[u]=low[u]=++tim;
	vis[u]=true;
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

int inDeg[MAXN];
bitset<MAXN> f[MAXN];
queue<int> Q;

int main(void){
	reg int T=read();
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		tim=0,memset(dfn,0,sizeof(dfn));
		top=0,scc_cnt=0,memset(col,0,sizeof(col));
		memset(inDeg,0,sizeof(inDeg));
		n=read(),m=read();
		for(reg int i=1;i<=m;++i){
			u[i]=read(),v[i]=read();
			Add_Edge(u[i],v[i]);
		}
		for(reg int i=1;i<=n;++i)
			if(!dfn[i])
				tarjan(i);
		cnt=0,memset(head,0,sizeof(head));
		for(reg int i=1;i<=m;++i)
			if(col[u[i]]!=col[v[i]]){
				Add_Edge(col[v[i]],col[u[i]]);
				++inDeg[col[u[i]]];
			}
		for(reg int i=1;i<=scc_cnt;++i){
			f[i].reset();
			f[i][i]=true;
			if(!inDeg[i])
				Q.push(i);
		}
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				--inDeg[v];
				f[v]|=f[u];
				if(!inDeg[v])
					Q.push(v);
			}
		}
		reg bool flag=true;
		for(reg int i=1;i<=scc_cnt&&flag;++i)
			for(reg int j=i+1;j<=scc_cnt&&flag;++j)
				if(!f[i][j]&&!f[j][i])
					flag=false;
		puts(flag?"Yes":"No");
	}
	return 0;
}