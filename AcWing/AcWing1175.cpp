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

inline int add(reg int a,reg int b,reg int mod){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

const int MAXN=1e5+5;
const int MAXM=1e6+5;

int n,m,x;
int a[MAXM],b[MAXM];
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
		reg int v;
		++scc_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			++siz[scc_cnt];
			col[v]=scc_cnt;
		}while(u!=v);
	}
	return;
}

int inDeg[MAXN];
int f[MAXN],g[MAXN];

struct Edge{
	int u,v;
	inline Edge(reg int u=0,reg int v=0):u(u),v(v){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return u==a.u?v<a.v:u<a.u;
	}
	inline bool operator==(const Edge& a)const{
		return u==a.u&&v==a.v;
	}
};

Edge E[MAXM];

int main(void){
	n=read(),m=read(),x=read();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read();
		Add_Edge(a[i],b[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	cnt=0,memset(head,0,sizeof(head));
	reg int tot=0;
	for(reg int i=1;i<=m;++i)
		if(col[a[i]]!=col[b[i]])
			E[++tot]=Edge(col[a[i]],col[b[i]]);
	sort(E+1,E+tot+1);
	tot=unique(E+1,E+tot+1)-(E+1);
	for(reg int i=1;i<=tot;++i){
		++inDeg[E[i].v];
		Add_Edge(E[i].u,E[i].v);
	}
	queue<int> Q;
	for(int i=1;i<=scc_cnt;++i)
		if(!inDeg[i]){
			f[i]=siz[i],g[i]=1;
			Q.push(i);
		}
	reg int ptr=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		if(f[ptr]<f[u])
			ptr=u;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			--inDeg[v];
			if(!inDeg[v])
				Q.push(v);
			if(f[v]<f[u]+siz[v]){
				f[v]=f[u]+siz[v];
				g[v]=0;
			}
			if(f[v]==f[u]+siz[v])
				g[v]=add(g[v],g[u],x);
		}
	}
	reg int ans1=f[ptr],ans2=0;
	for(reg int i=1;i<=scc_cnt;++i)
		if(f[i]==ans1)
			ans2=add(ans2,g[i],x);
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}