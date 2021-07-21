#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=5e4+5;

int n,W;
int w[MAXN],v[MAXN];
int cnt,head[MAXN],to[MAXN],nxt[MAXN];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs(reg int u){
	siz[u]=1;
	rnk[dfn[u]=++tim]=u;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		dfs(v);
		siz[u]+=siz[v];
	}
	return;
}

const int MAXSIZE=7e7+5;
const int inf=0x3f3f3f3f;

int f[MAXSIZE];

inline int getId(reg int i,reg int j){
	return (i-1)*(W+1)+j;
}

bool ed;

int main(void){
	n=read(),W=read();
	for(reg int i=1;i<=n;++i)
		Add_Edge(read(),i);
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read();
	dfs(0);
	for(reg int i=1;i<=tim;++i)
		for(reg int j=0;j<=W;++j)
			f[getId(i,j)]=-inf;
	for(reg int j=0;j<=W;++j)
		f[getId(1,j)]=0;
	for(reg int i=1;i<=tim;++i){
		for(reg int j=W;j>=w[rnk[i]];--j)
			f[getId(i+1,j)]=max(f[getId(i+1,j)],f[getId(i,j-w[rnk[i]])]+v[rnk[i]]);
		for(reg int j=0;j<=W;++j)
			f[getId(i+siz[rnk[i]],j)]=max(f[getId(i+siz[rnk[i]],j)],f[getId(i,j)]);
	}
	reg int ans=0;
	for(reg int j=0;j<=W;++j)
		ans=max(ans,f[getId(tim+1,j)]);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}