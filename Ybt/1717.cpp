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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=300+5;
const int MAXM=MAXN*(MAXN-1);
const int MAXLOG2N=9+1;

int n,m;
int dis[MAXLOG2N][MAXN][MAXN];
int f[MAXN][MAXN],g[MAXN][MAXN];

int main(void){
	memset(dis,0x3f,sizeof(dis));
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		dis[0][u][v]=w;
	}
	for(reg int i=1;i<=n;++i)
		dis[0][i][i]=0;
	for(reg int r=1;r<MAXLOG2N;++r)
		for(reg int k=1;k<=n;++k)
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=n;++j)
					dis[r][i][j]=min(dis[r][i][j],dis[r-1][i][k]+dis[r-1][k][j]);
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=n;++i)
		f[i][i]=0;
	int ans=0;
	for(reg int r=MAXLOG2N-1;r>=0;--r){
		memset(g,0x3f,sizeof(g));
		for(reg int k=1;k<=n;++k)
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=n;++j)
					g[i][j]=min(g[i][j],min(dis[r][i][k]+f[k][j],f[i][k]+dis[r][k][j]));
		reg bool flag=false;
		for(reg int i=1;i<=n;++i)
			if(g[i][i]<0){
				flag=true;
				break;
			}
		if(!flag){
			ans|=(1<<r);
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=n;++j)
					f[i][j]=g[i][j];
		}
	}
	if(ans>=n)
		puts("0");
	else
		printf("%d\n",ans+1);
	return 0;
}