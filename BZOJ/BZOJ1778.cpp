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

const int MAXN=300+5;

int n,m,p,q;
int deg[MAXN];
vector<int> V[MAXN];
double G[MAXN][MAXN];

inline void Gauss(void){
	for(reg int i=1;i<=n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(fabs(G[j][i])>fabs(G[Max][i]))
				Max=j;
		for(reg int j=1;j<=n+1;++j)
			swap(G[i][j],G[Max][j]);
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				reg double d=G[j][i]/G[i][i];
				for(reg int k=i;k<=n+1;++k)
					G[j][k]-=d*G[i][k];
			}
	}
	return;
}

int main(void){
	n=read(),m=read(),p=read(),q=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		++deg[a],++deg[b];
		V[a].push_back(b),V[b].push_back(a);
	}
	for(reg int i=1;i<=n;++i){
		if(i==1)
			G[i][n+1]=1;
		G[i][i]=1;
		for(reg int j=0,siz=V[i].size();j<siz;++j){
			reg int v=V[i][j];
			G[i][v]=1.0*(p-q)/(q*deg[v]);
		}
	}
	Gauss();
	for(reg int i=1;i<=n;++i)
		printf("%.9lf\n",G[i][n+1]/G[i][i]*p/q);
	return 0;
}