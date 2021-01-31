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

const int MAXN=200+5;
const int MAXS=16;
const double eps=1e-8;

int n,m,k,q;
bool vis[MAXN];
double u[MAXN];
vector<pair<int,double>/**/> V[MAXN];
double G[MAXN][MAXN];

inline void Gauss(void){
	for(reg int i=1;i<=n+1;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n+1;++j)
			if(fabs(G[j][i])>fabs(G[Max][i]))
				Max=j;
		for(reg int j=1;j<=n+2;++j)
			swap(G[i][j],G[Max][j]);
		for(reg int j=1;j<=n+1;++j)
			if(i!=j){
				reg double d=G[j][i]/G[i][i];
				for(reg int k=1;k<=n+2;++k)
					G[j][k]-=d*G[i][k];
			}
	}
	return;
}

char str[MAXN][MAXN][MAXS];

int main(void){
	n=read(),m=read(),k=read(),q=read();
	for(reg int i=1;i<=k;++i){
		static int id;
		id=read();
		vis[id]=true;
		u[id]=read();
	}
	for(reg int i=1;i<=m;++i){
		static int u,v;
		static double r;
		u=read(),v=read(),r=read();
		if(r<eps) r=eps;
		if(!u) u=n+1;
		if(!v) v=n+1;
		V[u].push_back(make_pair(v,r)),V[v].push_back(make_pair(u,r));
	}
	for(reg int i=1;i<=n;++i)
		if(!vis[i])
			for(reg int j=0,siz=V[i].size();j<siz;++j){
				reg int v=V[i][j].first,r=V[i][j].second;
				G[i][i]+=1.0/r,G[i][v]-=1.0/r;
			}
		else
			G[i][i]=1,G[i][n+1]=-1,G[i][n+2]=u[i];
	G[n+1][n+1]=1;
	Gauss();
	for(reg int i=1;i<=n+1;++i)
		u[i]=G[i][n+2]/G[i][i];
	for(reg int i=1;i<=n+1;++i)
		for(reg int j=1;j<=n+1;++j)
			sprintf(str[i][j],"%.2lf",u[i]-u[j]);
	for(reg int i=1;i<=q;++i){
		static int a,b;
		a=read(),b=read();
		if(!a) a=n+1;
		if(!b) b=n+1;
		puts(str[a][b]);
	}
	return 0;
}