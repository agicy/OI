#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1000000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;

int n,k;
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
double f[MAXN];
double ans;

inline void dfs(reg int u){
	siz[u]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
		siz[u]+=siz[v];
	}
	if(siz[u]==1)
		f[u]=1.0;
	else{
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			f[u]=max(f[u],min(f[v],1.0*siz[v]/(siz[u]-1)));
		}
		if(siz[u]>k)
			ans=max(ans,f[u]);
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=2;i<=n;++i)
		Add_Edge(read(),i);
	dfs(1);
	printf("%.10lf\n",ans);
	return 0;
}