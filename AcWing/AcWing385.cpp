#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100+5;
const int inf=0x3f3f3f3f;

int n,m;
int G[MAXN][MAXN];

int main(void){
	memset(G,0x3f,sizeof(G));
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		G[a][b]=G[b][a]=1;
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
	int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(G[i][j]<inf)
				ans=max(ans,G[i][j]);
	printf("%d\n",ans);
	return 0;
}