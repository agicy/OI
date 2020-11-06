#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e4+5;
const int MAXM=1e3+5;
const int inf=0x3f3f3f3f;

int n,m,k;
int x[MAXN],y[MAXN];
int up[MAXN],dn[MAXN];
int sum[MAXN];
int f[MAXN][MAXM*2];

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=n;++i){
		x[i]=read(),y[i]=read();
		up[i]=m,dn[i]=1;
	}
	up[n]=m,dn[n]=1;
	for(reg int i=1;i<=k;++i){
		static int p,l,h;
		p=read(),l=read(),h=read();
		sum[p]=1;
		up[p]=h-1,dn[p]=l+1;
	}
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=m;++i)
		f[0][i]=0;
	for(reg int i=1;i<=n;++i){
		for(reg int j=x[i]+1;j<=x[i]+m;++j)
			f[i][j]=min(f[i-1][j-x[i]],f[i][j-x[i]])+1;
		for(reg int j=m+1;j<=m+x[i];++j)
			f[i][m]=min(f[i][m],f[i][j]);
		for(reg int j=1;j<=m-y[i];++j)
			f[i][j]=min(f[i][j],f[i-1][j+y[i]]);
		for(reg int j=0;j<dn[i];++j)
			f[i][j]=inf;
		for(reg int j=up[i]+1;j<=m;++j)
			f[i][j]=inf;
	}
	int Min=inf;
	for(reg int i=dn[n];i<=up[n];++i)
		if(f[n][i]<Min)
			Min=f[n][i];
	if(Min>=inf){
		for(reg int i=1;i<=n;++i)
			sum[i]+=sum[i-1];
		for(reg int i=n;i>=0;--i)
			for(reg int j=dn[i];j<=up[i];++j)
				if(f[i][j]<inf){
					printf("0\n%d\n",sum[i]);
					return 0;
				}
	}
	else
		printf("1\n%d\n",Min);
	return 0;
}