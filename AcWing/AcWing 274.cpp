#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXL=200+5;
const int MAXN=1000+5;

int L,n;
int w[MAXL][MAXL];
int f[MAXN][MAXL][MAXL];
int p[MAXN];

int main(void){
	L=read(),n=read();
	for(reg int i=1;i<=L;++i)
		for(reg int j=1;j<=L;++j)
			w[i][j]=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	p[0]=3;
	memset(f,0X3F,sizeof(f));
	f[0][1][2]=0;
	for(reg int i=0;i<n;++i)
		for(reg int j=1;j<=L;++j)
			for(reg int k=1;k<=L;++k){
				reg int l=p[i],v=f[i][j][k];
				if(j==k||j==l||k==l)
					continue;
				reg int pos=p[i+1];
				f[i+1][j][k]=min(f[i+1][j][k],v+w[l][pos]);
				f[i+1][l][k]=min(f[i+1][l][k],v+w[j][pos]);
				f[i+1][j][l]=min(f[i+1][j][l],v+w[k][pos]);
			}
	int ans=INF;
	for(reg int i=1;i<=L;++i)
		for(reg int j=1;j<=L;++j){
			reg int k=p[n];
			if(i==j||i==k||j==k)
				continue;
			ans=min(ans,f[n][i][j]);
		}
	printf("%d\n",ans);
	return 0;
}
