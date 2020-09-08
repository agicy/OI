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

const int MAXN=2e3+5;
const int inf=0x3f3f3f3f;

int n;
int g[MAXN][MAXN];
bool vis[MAXN];
int dis[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j<=n;++j){
			static int x;
			x=read();
			g[i-1][j]=g[j][i-1]=x;
		}
	reg ll ans=0;
	dis[0]=0;
	for(reg int i=1;i<=n;++i)
		dis[i]=g[0][i];
	for(reg int i=1;i<=n;++i){
		reg int Min=inf,pos=0;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&dis[j]<Min)
				Min=dis[j],pos=j;
		vis[pos]=true;
		ans+=Min;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&dis[j]>g[pos][j])
				dis[j]=g[pos][j];
	}
	printf("%lld\n",ans);
	return 0;
}