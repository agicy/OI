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

const int MAXN=1e3+5;
const int MAXM=1e3+5;

int n,m,x,y;
double M[MAXN][MAXM];
double f[MAXN][MAXM];

inline void Gauss(void){
	for(reg int i=1;i<m;++i){
		M[i][i+1]/=M[i][i],M[i][m+1]/=M[i][i];
		M[i][i]=1;
		M[i+1][i+1]-=M[i+1][i]*M[i][i+1],M[i+1][m+1]-=M[i+1][i]*M[i][m+1];
		M[i+1][i]=0;
	}
	M[m][m+1]/=M[m][m],M[m][m]=1;
	for(reg int i=m-1;i>=1;--i)
		M[i][m+1]-=M[i+1][m+1]*M[i][i+1];
	return;
}

int main(void){
	n=read(),m=read(),x=read(),y=read();
	for(reg int i=n-1;i>=x;--i){
		if(m==1)
			M[1][1]=-0.5,M[1][2]=-0.5*f[i+1][1]-1;
		else{
			M[1][1]=-2.0/3.0,M[1][2]=1.0/3.0,M[1][m+1]=-f[i+1][1]/3.0-1.0;
			for(reg int j=2;j<m;++j)
				M[j][j]=-0.75,M[j][j-1]=M[j][j+1]=0.25,M[j][m+1]=-0.25*f[i+1][j]-1;
			M[m][m]=-2.0/3.0,M[m][m-1]=1.0/3.0,M[m][m+1]=-f[i+1][m]/3.0-1.0;
		}
		Gauss();
		for(reg int j=1;j<=m;++j)
			f[i][j]=M[j][m+1];
	}
	printf("%.10lf\n",f[x][y]);
	return 0;
}