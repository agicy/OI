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

inline void cMax(reg int &a,reg int b){
	if(a<b) a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXE=1e5+5;
const int MAXV=MAXE;

namespace sieve{
	bool vis[MAXE];
	int tot,prime[MAXE];
	inline void Init(reg int n){
		for(reg int i=2;i<=n;++i){
			if(!vis[i])
				prime[++tot]=i;
			for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
				vis[i*prime[j]]=true;
				if(!(i%prime[j]))
					break;
			}
		}
		return;
	}
}

namespace Graph{
	const int MAXE=5e6;
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
	int scc_cnt,col[MAXV];
	inline void tarjan(reg int u){
		vis[u]=true;
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(reg int i=head[u],v;i;i=Next[i]){
			v=to[i];
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
			}while(v!=u);
		}
		return;
	}
	int bak_cnt,bak_head[MAXV];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=sieve::tot&&i*sieve::prime[j]<=n;++j)
				Add_Edge(i,i*sieve::prime[j]);
		bak_cnt=cnt,memcpy(bak_head,head,sizeof(head));
		return;
	}
	inline void roll_back(void){
		tim=0;
		memset(dfn,0,sizeof(dfn));
		cnt=bak_cnt,memcpy(head,bak_head,sizeof(bak_head));
		return;
	}
}

int n,Max;
int w[MAXN],e[MAXN];

int main(void){
	reg int t=read();
	sieve::Init(1e5);
	Graph::Init(1e5);
	while(t--){
		n=read();
		Max=0;
		for(reg int i=1;i<=n;++i)
			cMax(Max,w[i]=read());
		for(reg int i=1;i<=n;++i){
			cMax(Max,e[i]=read());
			Graph::Add_Edge(w[i],e[i]);
		}
		for(reg int i=1;i<=Max;++i)
			if(!Graph::dfn[i])
				Graph::tarjan(i);
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			if(Graph::col[w[i]]==Graph::col[e[i]])
				++ans;
		printf("%d\n",ans);
		if(t)
			Graph::roll_back();
	}
	return 0;
}