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

const int MAXN=5e3+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n;
int df[MAXN];
vector<int> G[MAXN];
int siz[MAXN];
int tmp[MAXN];
int f[MAXN][MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	f[u][1]=1;
	for(int v:G[u])
		if(v!=father){
			dfs(v,u);
			for(reg int i=0;i<=siz[u];++i)
				tmp[i]=f[u][i],f[u][i]=0;
			for(reg int i=0;i<=siz[u];++i)
				for(reg int j=0;j<=siz[v];++j)
					f[u][i+j]=add(f[u][i+j],1ll*tmp[i]*f[v][j]%mod);
			siz[u]+=siz[v];
		}
	for(reg int i=2;i<=siz[u];i+=2)
		f[u][0]=sub(f[u][0],1ll*df[i-1]*f[u][i]%mod);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		G[x].push_back(y),G[y].push_back(x);
	}
	df[0]=df[1]=1;
	for(reg int i=2;i<=n;++i)
		df[i]=1ll*df[i-2]*i%mod;
	dfs(1,0);
	printf("%d\n",sub(0,f[1][0]));
	return 0;
}