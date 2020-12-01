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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e3+5;
const int p=786433;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int n,k;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int f[MAXN][MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1,f[u][1]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			static int g[MAXN];
			for(reg int i=0;i<=siz[u]+siz[v];++i)
				g[i]=0;
			for(reg int j=0;j<=siz[v];++j)
				for(reg int i=1;i<=siz[u];++i)
					g[i+j]=add(g[i+j],1ll*f[v][j]*f[u][i]%p);
			for(reg int i=0;i<=siz[u]+siz[v];++i)
				f[u][i]=g[i];
			siz[u]+=siz[v];
		}
	}
	for(reg int i=k;i<=siz[u];++i)
		f[u][0]=add(f[u][0],f[u][i]);
	return;
}

int main(void){
	freopen("cut.in","r",stdin);
	freopen("cut.out","w",stdout);

	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs(1,0);
	printf("%d\n",f[1][0]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}