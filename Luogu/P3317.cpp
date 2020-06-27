#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define eps 1e-6

const int MAXN=50+5;

int n;
double G[MAXN][MAXN];

inline double Gauss(void){
	reg double ans=1;
	for(reg int i=1;i<n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(fabs(G[Max][i])<fabs(G[j][i]))
				Max=j;
		if(Max!=i)
			swap(G[i],G[Max]);
		for(reg int j=i+1;j<n;++j){
			reg double t=G[j][i]/G[i][i];
			for(reg int k=i;k<n;++k)
				G[j][k]-=t*G[i][k];
		}
		ans*=G[i][i];
	}
	return fabs(ans);
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			scanf("%lf",&G[i][j]);
	reg double ans=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			if(fabs(G[i][j])<eps)
				G[i][j]=eps;
			if(fabs(1-G[i][j])<eps)
				G[i][j]=1-eps;
			if(i<j)
				ans*=(1-G[i][j]);
			G[i][j]/=(1-G[i][j]);
		}
	for(reg int i=1;i<=n;++i){
		G[i][i]=0;
		for(reg int j=1;j<=n;++j)
			if(i!=j)
				G[i][i]-=G[i][j];
	}
	ans*=Gauss();
	printf("%.6f\n",ans);
	return 0;
}