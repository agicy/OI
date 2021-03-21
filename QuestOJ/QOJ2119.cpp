#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=3e3+5;
const double pi=acos(-1.0);

int n;
double a[MAXN],b[MAXN],c[MAXN];
int binom[5][5];
double f[2][5][5][5],E[5][5][5];

int main(void){
	binom[0][0]=1;
	for(reg int i=1;i<=4;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=binom[i-1][j]+binom[i-1][j-1];
	}
	while(scanf("%d",&n)!=EOF&&n){
		memset(f,0,sizeof(f));
		for(reg int i=1;i<=n;++i){
			static double alpha,beta,L;
			scanf("%lf%lf%lf",&alpha,&beta,&L);
			a[i]=L*cos(beta)*cos(alpha),b[i]=L*cos(beta)*sin(alpha),c[i]=L*sin(beta);
		}
		f[0][0][0][0]=1;
		for(reg int i=1;i<=n;++i){
			static double sa[5],sb[5],sc[5];
			sa[0]=sb[0]=sc[0]=1;
			for(reg int j=1;j<=4;++j){
				sa[j]=sa[j-1]*a[i];
				sb[j]=sb[j-1]*b[i];
				sc[j]=sc[j-1]*c[i];
			}
			for(reg int j=0;j<=4;++j)
				for(reg int k=0;j+k<=4;++k)
					for(reg int l=0;j+k+l<=4;++l)
						E[j][k][l]=sa[j]*sb[k]*sc[l]/(j+k+l+1);
			for(reg int j=0;j<=4;++j)
				for(reg int k=0;j+k<=4;++k)
					for(reg int l=0;j+k+l<=4;++l){
						f[i&1][j][k][l]=0;
						for(reg int x=0;x<=j;++x)
							for(reg int y=0;y<=k;++y)
								for(reg int z=0;z<=l;++z)
									f[i&1][j][k][l]+=f[(i-1)&1][j-x][k-y][l-z]*E[x][y][z]*binom[j][x]*binom[k][y]*binom[l][z];
					}
		}
		reg double ans=(f[n&1][4][0][0]+f[n&1][0][4][0]+f[n&1][0][0][4]+2.0*(f[n&1][2][2][0]+f[n&1][2][0][2]+f[n&1][0][2][2]))/3.0*pi;
		printf("%.9lf\n",ans);
	}
	return 0;
}