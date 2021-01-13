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

const int MAXN=1e5+5;
const int MAXK=100+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){return a+=b,a>=p?a-p:a;}
inline int add(reg int a,reg int b,reg int c){return add(add(a,b),c);}
inline int add(reg int a,reg int b,reg int c,reg int d){return add(add(a,b),add(c,d));}

int n,k;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int f[MAXN][MAXK][2][2];
int g[MAXK][2][2];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	f[u][0][0][0]=f[u][1][1][0]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			memcpy(g,f[u],sizeof(f[u]));
			memset(f[u],0,sizeof(f[u]));
			for(reg int i=0;i<=min(siz[u],k);++i){
				for(reg int j=0;j<=min(siz[v],k-i);++j){
					f[u][i+j][0][0]=add(
						f[u][i+j][0][0],
						1ll*g[i][0][0]*f[v][j][0][1]%p //u 放 i 个，v 放 j 个
					);
					f[u][i+j][0][1]=add(
						f[u][i+j][0][1],
						1ll*g[i][0][0]*f[v][j][1][1]%p, //v 放 -> u 可见
						1ll*g[i][0][1]*add(f[v][j][1][1],f[v][j][0][1])%p //u 可见 -> v 随便
					);
					f[u][i+j][1][0]=add(
						f[u][i+j][1][0],
						1ll*g[i][1][0]*add(f[v][j][0][0],f[v][j][0][1])%p //u 不可见 -> v 不放
					);
					f[u][i+j][1][1]=add(
						f[u][i+j][1][1],
						1ll*g[i][1][0]*add(f[v][j][1][0],f[v][j][1][1])%p,
						1ll*g[i][1][1]*add(f[v][j][0][0],f[v][j][0][1],f[v][j][1][0],f[v][j][1][1])%p
					);
				}
			}
			siz[u]+=siz[v];
		}
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(1,0);
	printf("%d\n",add(f[1][k][0][1],f[1][k][1][1]));
	return 0;
}