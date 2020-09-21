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

const int MAXN=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

ll dis[MAXN];
queue<int> Q;

inline void bfs(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]==inf){
				dis[v]=dis[u]+w[i];
				Q.push(v);
			}
		}
	}
	return;
}

ll Max[MAXN][2];

inline void dfs(reg int u,reg int father,reg int id){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			Max[v][id]=Max[u][id]+w[i];
			dfs(v,u,id);
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,t;
		u=read(),v=read(),t=read();
		Add_Edge(u,v,t);
		Add_Edge(v,u,t);
	}
	bfs(1);
	reg int r1=1;
	for(reg int i=1;i<=n;++i)
		if(dis[i]>dis[r1])
			r1=i;
	bfs(r1);
	reg int r2=r1;
	for(reg int i=1;i<=n;++i)
		if(dis[i]>dis[r2])
			r2=i;
	dfs(r1,0,0),dfs(r2,0,1);
	ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,min(Max[i][0],Max[i][1]));
	printf("%lld\n",ans+dis[r2]);
	return 0;
}