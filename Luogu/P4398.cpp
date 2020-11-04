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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50+1;

int n;
int a[MAXN][MAXN],b[MAXN][MAXN];
int f[MAXN][MAXN][MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			a[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			b[i][j]=read();
	int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			for(reg int k=1;k<=n;++k)
				for(reg int l=1;l<=n;++l)
					if(a[i][j]==b[k][l]){
						f[i][j][k][l]=min(f[i-1][j-1][k-1][l-1],min(f[i-1][j][k-1][l],f[i][j-1][k][l-1]))+1;
						ans=max(ans,f[i][j][k][l]);
					}
	printf("%d\n",ans);
	return 0;
}