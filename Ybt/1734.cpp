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

const int MAXN=1e5+5;
const int MAXM=1e6+5;
const int p=1000;

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

int n,m,q;
int u[MAXM],v[MAXM],id[MAXM];
int cnt=1,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int fa[MAXN],siz[MAXN];

inline void dfs(reg int u){
	siz[u]=1;
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			fa[v]=fa[u];
			dfs(v);
			siz[u]+=siz[v];
		}
	}
	return;
}

int tim,dfn[MAXN],low[MAXN];
bool bri[MAXM<<1];

inline void tarjan(reg int u,reg int pre){
	dfn[u]=low[u]=++tim;
	for(reg int i=head[u];i;i=Next[i]){
		if((i^1)==pre)
			continue;
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,i);
			cMin(low[u],low[v]);
			if(low[v]>dfn[u])
				bri[i]=bri[i^1]=true;
		}
		else
			cMin(low[u],dfn[v]);
	}
	return;
}

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=0;i<m;++i){
		u[i]=read(),v[i]=read();
		Add_Edge(u[i],v[i]);
		Add_Edge(v[i],u[i]);
		id[i]=cnt;
	}
	reg ll ans=0;
	for(reg int i=0;i<n;++i)
		if(!vis[i]){
			fa[i]=i;
			dfs(i);
			ans+=1ll*siz[i]*(n-siz[i]);
		}
	ans=(ans>>1)%p;
	for(reg int i=0;i<n;++i)
		if(!dfn[i])
			tarjan(i,0);
	while(q--){
		static int x;
		x=read();
		if(!bri[id[x]])
			printf("%lld\n",ans);
		else{
			reg int s1=(siz[u[x]]<siz[v[x]]?siz[u[x]]:siz[v[x]]);
			reg int s2=siz[fa[u[x]]]-s1;
			printf("%lld\n",(ans+1ll*s1*s2)%p);
		}
	}
	return 0;
}