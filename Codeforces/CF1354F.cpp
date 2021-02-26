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

const int MAXN=75+5;

int n,k;
int a[MAXN],b[MAXN];
int id[MAXN];
int f[MAXN][MAXN];
bool g[MAXN][MAXN];
bool vis[MAXN];

inline bool cmp(reg int x,reg int y){
	return b[x]<b[y];
}

inline void dfs(reg int n,reg int k){
	if(!n)
		return;
	if(g[n][k])
		vis[n]=true,dfs(n-1,k-1);
	else
		vis[n]=false,dfs(n-1,k);
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),k=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read(),b[i]=read(),id[i]=i;
		sort(id+1,id+n+1,cmp);
		memset(f,0xcf,sizeof(f));
		f[0][0]=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<=i&&j<=k;++j){
				f[i][j]=f[i-1][j]+b[id[i]]*(k-1),g[i][j]=false;
				if(j&&f[i-1][j-1]+a[id[i]]+b[id[i]]*(j-1)>f[i][j])
					f[i][j]=f[i-1][j-1]+a[id[i]]+b[id[i]]*(j-1),g[i][j]=true;
			}
		dfs(n,k);
		printf("%d\n",k-1+(n-k)*2+1);
		reg int las=0;
		for(reg int i=1;i<=n;++i)
			if(vis[i]){
				++las;
				if(las==k){
					las=id[i];
					break;
				}
				printf("%d ",id[i]);
			}
		for(reg int i=1;i<=n;++i)
			if(!vis[i])
				printf("%d %d ",id[i],-id[i]);
		printf("%d\n",las);
	}
	return 0;
}