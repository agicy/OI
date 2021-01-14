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

const int MAXN=1e5+5;
const int MAXNM=1e8+5;

int n,m;
int s[MAXN];
vector<int> f[MAXN];
int siz[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void dfs(reg int u){
	siz[u]=1;
	f[u].resize(siz[u]+1,0);
	f[u][1]=s[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
		f[u].resize(siz[u]+siz[v]+1,0);
		for(reg int j=min(m+1,siz[u]+siz[v]);j>=1;--j)
			for(reg int k=max(1,j-siz[u]);k<=min(j-1,siz[v]);++k)
				f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]);
		siz[u]+=siz[v];
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int k;
		k=read(),s[i]=read();
		Add_Edge(k,i);
	}
	dfs(0);
	printf("%d\n",f[0][m+1]);
	return 0;
}