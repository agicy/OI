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
const int MAXM=1e4+5;
const int MAXLOG2W=30;

int n,m;
int deg[MAXN];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

long double f[MAXN][MAXN];

inline long double solve(reg int dir){
	f[n][n]=1;
	for(reg int i=1;i<n;++i){
		memset(f[i],0,sizeof(f[i]));
		f[i][i]=deg[i];
		reg int cnt=0;
		for(reg int j=head[i];j;j=Next[j]){
			reg int v=to[j];
			if((w[j]>>dir)&1)
				++cnt,++f[i][v];
			else
				--f[i][v];
		}
		f[i][n+1]=cnt;
	}
	for(reg int i=1;i<=n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(fabs(f[j][i])>fabs(f[Max][i]))
				Max=j;
		for(reg int j=1;j<=n+1;++j)
			swap(f[i][j],f[Max][j]);
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				reg double d=f[j][i]/f[i][i];
				for(reg int k=i+1;k<=n+1;++k)
					f[j][k]-=f[i][k]*d;
			}
	}
	return f[1][n+1]/f[1][1];
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		++deg[u],Add_Edge(u,v,w);
		if(u!=v)
			++deg[v],Add_Edge(v,u,w);
	}
	reg long double ans=0;
	for(reg int i=0;i<MAXLOG2W;++i)
		ans+=pow(2,i)*solve(i);
	printf("%.3Lf\n",ans);
	return 0;
}