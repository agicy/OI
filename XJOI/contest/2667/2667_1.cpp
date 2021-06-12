#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e3+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n;
int x[MAXN],y[MAXN];
int sumx[MAXN],sumy[MAXN];
ll f[MAXN][MAXN];

inline ll sqr(reg ll x){
	return x*x;
}

inline ll getValx(reg int l,reg int r){
	return sqr(sumx[r]-sumx[l-1]);
}

inline ll getValy(reg int l,reg int r){
	return sqr(sumy[r]-sumy[l-1]);
}

const int B=5;

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			x[i]=read();
		x[n+1]=0;
		for(reg int i=1;i<=n;++i)
			y[i]=read();
		y[n+1]=0;
		for(reg int i=1;i<=n+1;++i)
			sumx[i]=sumx[i-1]+x[i],sumy[i]=sumy[i-1]+y[i];
		for(reg int i=0;i<=n+1;++i)
			for(reg int j=0;j<=n+1;++j)
				f[i][j]=-inf;
		f[0][0]=0;
		for(reg int i=0;i<=n;++i)
			for(reg int j=0;j<=n;++j)
				if(f[i][j]!=-inf){
					f[i+1][j+1]=max(f[i+1][j+1],f[i][j]+x[i+1]*y[j+1]);
					for(reg int k=j+2,cnt=0;k<=n+1&&(++cnt<=B);++k)
						f[i+1][k]=max(f[i+1][k],f[i][j]+x[i+1]*y[k]-getValy(j+1,k-1));
					for(reg int k=i+2,cnt=0;k<=n+1&&(++cnt<=B);++k)
						f[k][j+1]=max(f[k][j+1],f[i][j]+x[k]*y[j+1]-getValx(i+1,k-1));
				}
		printf("%lld\n",f[n+1][n+1]);
		fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	}
	return 0;
}