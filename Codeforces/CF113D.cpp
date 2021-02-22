#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=22+5;
const int MAXM=MAXN*(MAXN-1)/2;

int n,m,a,b;
int deg[MAXN];
vector<int> G[MAXN];
double p[MAXN];

inline void Add_Edge(reg int u,reg int v){
	G[u].push_back(v);
	return;
}

inline int getId(reg int i,reg int j){
	return (i-1)*n+j;
}

int tot;
double M[MAXN*MAXN][MAXN*MAXN];

inline void Gauss(void){
	for(reg int i=1;i<=tot;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=tot;++j)
			if(fabs(M[j][i])>fabs(M[Max][i]))
				Max=j;
		for(reg int j=1;j<=tot+1;++j)
			swap(M[i][j],M[Max][j]);
		for(reg int j=1;j<=tot;++j)
			if(i!=j){
				reg double d=M[j][i]/M[i][i];
				for(reg int k=i;k<=tot+1;++k)
					M[j][k]-=d*M[i][k];
			}
	}
	for(reg int i=1;i<=tot;++i)
		M[i][tot+1]/=M[i][i];
	return;
}

int main(void){
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(reg int i=1;i<=m;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		++deg[u],++deg[v];
		Add_Edge(u,v),Add_Edge(v,u);
	}
	for(reg int i=1;i<=n;++i)
		scanf("%lf",&p[i]);
	tot=n*n;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=n;++j){
			reg int id=getId(i,j);
			if(i!=j)
				M[id][id]=1-p[i]*p[j];
			else
				M[id][id]=1;
			for(int u:G[i])
				if(u!=j)
					M[id][getId(u,j)]=-(1.0-p[u])/deg[u]*p[j];
			for(int v:G[j])
				if(v!=i)
					M[id][getId(i,v)]=-(1.0-p[v])/deg[v]*p[i];
			for(int u:G[i])
				for(int v:G[j])
					if(u!=v)
						M[id][getId(u,v)]=-(1.0-p[u])/deg[u]*(1.0-p[v])/deg[v];
		}
	}
	M[getId(a,b)][tot+1]=1;
	Gauss();
	for(reg int i=1;i<=n;++i)
		printf("%.10lf%c",M[getId(i,i)][tot+1],i==n?'\n':' ');
	return 0;
}