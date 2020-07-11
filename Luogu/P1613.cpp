#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=50+5;

bool G[64][MAXN][MAXN];
int n,m;
int dis[MAXN][MAXN];

int main(void){
	memset(dis,0X3F,sizeof(dis));
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		dis[x][y]=1;
		G[0][x][y]=true;
	}
	for(reg int T=1;T<=63;++T)
		for(reg int k=1;k<=n;++k)
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=n;++j)
					if(G[T-1][i][k]&&G[T-1][k][j]){
						G[T][i][j]=true;
						dis[i][j]=1;
					}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	printf("%d\n",dis[1][n]);
	return 0;
}
