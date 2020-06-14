#include<bits/stdc++.h>
using namespace std;
#define reg register
#define eps 1e-8

const int MAXN=10+5;

double a[MAXN][MAXN],c[MAXN][MAXN];

int n;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n+1;++i)
		for(reg int j=1;j<=n;++j)
			scanf("%lf",&a[i][j]);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			c[i][j]=2.0*(a[i][j]-a[i+1][j]);
			c[i][n+1]+=a[i][j]*a[i][j]-a[i+1][j]*a[i+1][j];
		}
	for(reg int i=1;i<=n;++i){
		for(reg int j=i;j<=n;++j)
			if(fabs(c[j][i]>eps)){
				for(reg int k=1;k<=n;++k)
					swap(c[i][k],c[j][k]);
				swap(c[i][n+1],c[j][n+1]);
			}
		for(reg int j=1;j<=n;++j){
			if(i==j)
				continue;
			reg double rate=c[j][i]/c[i][i];
			for(int k=i;k<=n;k++)
				c[j][k]-=c[i][k]*rate;
			c[j][n+1]-=c[i][n+1]*rate;
		}
	}
	for(reg int i=1;i<=n;++i)
		printf("%.3f%c",c[i][n+1]/c[i][i],i==n?'\n':' ');
	return 0;
}