#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e3+5;
const int MAXM=2e5+5;

int n,m;
int G[MAXN][MAXM];
int sum[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		G[i][i]=m+1;
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		G[x][y]=i;
	}
	for(reg int k=n;k>=1;--k){
		for(reg int i=k;i<=n;++i)
			++sum[min(G[i][k],G[k][i])];
		for(reg int i=1;i<=k;++i)
			if(G[i][k])
				for(reg int j=1;j<=n;++j)
					G[i][j]=max(G[i][j],min(G[i][k],G[k][j]));
		for(reg int i=k+1;i<=n;++i)
			if(G[i][k])
				for(reg int j=1;j<k;++j)
					G[i][j]=max(G[i][j],min(G[i][k],G[k][j]));
	}
	for(reg int i=m;i>=1;--i)
		sum[i]+=sum[i+1];
	for(reg int i=1;i<=m+1;++i)
		write(sum[i]),putchar(i==m+1?'\n':' ');
	flush();
	return 0;
}