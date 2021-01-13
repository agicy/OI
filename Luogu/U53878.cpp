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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXNP=1e8+5;
const int inf=0x3f3f3f3f;

int n,p;
int outdeg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
vector<int> f[MAXN];

inline void dfs(reg int u){
	siz[u]=1;
	f[u].resize(siz[u]+1,inf);
	f[u][1]=outdeg[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
		siz[u]+=siz[v];
		f[u].resize(min(siz[u],p)+1,inf);
		for(reg int j=min(siz[u],p);j>=1;--j)
			for(reg int k=1;k<=min(j-1,siz[v]);++k)
				f[u][j]=min(f[u][j],f[u][j-k]+f[v][k]-1);
	}
	return;
}

int main(void){
	n=read(),p=read();
	for(reg int i=1;i<n;++i){
		static int I,J;
		I=read(),J=read();
		++outdeg[I];
		Add_Edge(I,J);
	}
	dfs(1);
	reg int ans=f[1][p];
	for(reg int i=2;i<=n;++i)
		if(siz[i]>=p)
			ans=min(ans,f[i][p]+1);
	printf("%d\n",ans);
	return 0;
}