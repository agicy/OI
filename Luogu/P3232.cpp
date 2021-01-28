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

const int MAXN=500+5;
const int MAXM=1.25e5+5;

int n,m;
int u[MAXM],v[MAXM];
int deg[MAXN];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

double G[MAXN][MAXN];
double p[MAXN];
double f[MAXM];

inline void Gauss(void){
	for(reg int i=1;i<=n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(fabs(G[Max][i])<fabs(G[j][i]))
				Max=j;
		for(reg int j=1;j<=n+1;++j)
			swap(G[i][j],G[Max][j]);
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				reg double d=G[j][i]/G[i][i];
				for(reg int k=i+1;k<=n+1;++k)
					G[j][k]-=G[i][k]*d;
			}
	}
	for(reg int i=1;i<=n;++i)
		p[i]=G[i][n+1]/G[i][i];
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		++deg[u[i]],++deg[v[i]];
		Add_Edge(u[i],v[i]),Add_Edge(v[i],u[i]);
	}
	for(reg int i=1;i<=n;++i){
		G[i][i]=1;
		for(reg int j=head[i];j;j=Next[j]){
			reg int v=to[j];
			if(v!=n)
				G[i][v]=-1.0/deg[v];
		}
		G[i][n+1]=(i==1)?1:0;
	}
	Gauss();
	for(reg int i=1;i<=m;++i){
		if(u[i]!=n)
			f[i]+=p[u[i]]/deg[u[i]];
		if(v[i]!=n)
			f[i]+=p[v[i]]/deg[v[i]];
	}
	sort(f+1,f+m+1);
	reg double ans=0;
	for(reg int i=1;i<=m;++i)
		ans+=f[i]*(m-i+1);
	printf("%.3lf\n",ans);
	return 0;
}