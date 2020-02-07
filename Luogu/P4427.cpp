#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 998244353
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

const int MAXN=300000+5;
const int MAXLOG2N=19+1;
const int MAXK=50+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int p[MAXN][MAXK];

inline void Init(reg int n){
	for(reg int i=1;i<=n;++i){
		p[i][0]=1;
		for(reg int j=1;j<MAXK;++j)
			p[i][j]=(ll)p[i][j-1]*i%MOD;
	}
	return;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	Init(n);
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

int sum[MAXN][MAXK];
int dep[MAXN];
int fa[MAXN][MAXLOG2N];

inline void DFS(reg int ID,reg int father){
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=0;i<MAXK;++i)
		sum[ID][i]=(sum[father][i]+p[dep[ID]][i])%MOD;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID);
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline void Work(void){
	dep[0]=-1;
	DFS(1,0);
	m=read();
	while(m--){
		static int u,v,k;
		u=read(),v=read(),k=read();
		reg int lca=LCA(u,v);
		reg int ans=(sum[u][k]+sum[v][k])%MOD-(sum[lca][k]+sum[fa[lca][0]][k])%MOD;
		printf("%d\n",(ans+MOD)%MOD);
	}
	return;
}
