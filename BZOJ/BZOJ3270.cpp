#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=20+5;
const int MAXN2=MAXN*MAXN;

int n,m,a,b;
int n2;
int deg[MAXN];
vector<int> G[MAXN];
double p[MAXN];
double M[MAXN2][MAXN2];

inline void Gauss(void){
	for(reg int i=1;i<=n2;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n2;++j)
			if(fabs(M[j][i])>fabs(M[Max][i]))
				Max=j;
		for(reg int j=1;j<=n2+1;++j)
			swap(M[i][j],M[Max][j]);
		for(reg int j=1;j<=n2;++j)
			if(i!=j){
				reg double d=M[j][i]/M[i][i];
				for(reg int k=i+1;k<=n2+1;++k)
					M[j][k]-=M[i][k]*d;
			}
	}
	return;
}

inline int getId(reg int i,reg int j){
	return (i-1)*n+j;
}

int main(void){
	n=read(),m=read(),a=read(),b=read();
	n2=n*n;
	for(reg int i=1;i<=n;++i)
		G[i].push_back(i);
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		++deg[u],++deg[v];
		G[u].push_back(v),G[v].push_back(u);
	}
	for(reg int i=1;i<=n;++i)
		scanf("%lf",&p[i]);
	for(reg int x=1;x<=n;++x)
		for(reg int y=1;y<=n;++y){
			reg int u=getId(x,y);
			M[u][u]=-1;
			for(vector<int>::iterator it=G[x].begin();it!=G[x].end();++it)
				for(vector<int>::iterator jt=G[y].begin();jt!=G[y].end();++jt){
					reg int i=*it,j=*jt,v=getId(i,j);
					if(i==j)
						continue;
					if(i==x&&j==y)
						M[u][v]+=p[x]*p[y];
					else if(i==x)
						M[u][v]+=p[x]*(1-p[j])/deg[j];
					else if(j==y)
						M[u][v]+=p[y]*(1-p[i])/deg[i];
					else
						M[u][v]+=(1-p[i])*(1-p[j])/deg[i]/deg[j];
				}
		}
	M[getId(a,b)][n2+1]=-1;
	Gauss();
	for(reg int i=1;i<=n;++i)
		printf("%.6lf ",M[getId(i,i)][n2+1]/M[getId(i,i)][getId(i,i)]);
	puts("");
	return 0;
}