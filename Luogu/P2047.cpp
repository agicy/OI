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

const int MAXN=100+5;

int n,m;
int dis[MAXN][MAXN];
ll cnt[MAXN][MAXN];

int main(void){
	n=read(),m=read();
	memset(dis,0x3f,sizeof(dis));
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		dis[a][b]=dis[b][a]=c;
		cnt[a][b]=cnt[b][a]=1;
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			if(k!=i)
				for(reg int j=1;j<=n;++j)
					if(i!=j&&j!=k){
						if(dis[i][k]+dis[k][j]==dis[i][j])
							cnt[i][j]+=cnt[i][k]*cnt[k][j];
						else if(dis[i][k]+dis[k][j]<dis[i][j]){
							dis[i][j]=dis[i][k]+dis[k][j];
							cnt[i][j]=cnt[i][k]*cnt[k][j];
						}
					}
	for(reg int k=1;k<=n;++k){
		reg double ans=0;
		for(reg int i=1;i<=n;++i)
			if(k!=i)
				for(reg int j=1;j<=n;++j)
					if(i!=j&&j!=k&&cnt[i][j])
						if(dis[i][k]+dis[k][j]==dis[i][j])
							ans+=cnt[i][k]*cnt[k][j]*1.0/cnt[i][j];
		printf("%.3lf\n",ans);
	}
	return 0;
}