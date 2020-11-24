#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const ll inf=0x1f1f1f1f1f1f1f1fll;

int n,m;
ll G[MAXN][MAXN];
ll dis[MAXN][MAXN];

int main(void){
	n=read(),m=read();
	memset(G,0x1f,sizeof(G));
	for(reg int i=1;i<=n;++i)
		G[i][i]=0;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		static ll d;
		u=read(),v=read(),d=read();
		G[u][v]=G[v][u]=min(G[u][v],d);
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			dis[i][j]=G[i][j];
	ll ans=inf;
	for(reg int k=1;k<=n;++k){
		for(reg int i=1;i<k;++i)
			for(reg int j=i+1;j<k;++j)
				ans=min(ans,dis[i][j]+G[i][k]+G[k][j]);
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				dis[i][j]=dis[j][i]=min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	if(ans==inf)
		puts("No solution.");
	else
		printf("%lld\n",ans);
	return 0;
}