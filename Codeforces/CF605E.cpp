#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e3+5;

int n;
double G[MAXN][MAXN];
double p[MAXN];
double dis[MAXN];
bool vis[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			G[i][j]=read()/100.0;
	if(n==1){
		puts("0");
		return 0;
	}
	for(reg int i=1;i<=n;++i)
		dis[i]=1,p[i]=1-G[i][n];
	vis[n]=true,dis[n]=0;
	for(reg int i=1;i<=n;++i){
		reg int ptr=0;
		reg double Max=INFINITY;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&dis[j]/(1-p[j])<Max)
				Max=dis[j]/(1-p[j]),ptr=j;
		vis[ptr]=1;
		if(ptr==1)
			return printf("%.10f\n",dis[1]/(1-p[1])),0;
		for(reg int j=1;j<=n;++j)
			dis[j]+=(dis[ptr]/(1-p[ptr]))*G[j][ptr]*p[j],p[j]*=(1-G[j][ptr]);
	}
	return 0;
}