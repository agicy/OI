#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

const int MAXN=1e5+5;
const int MAXK=20+5;

int n,k;
int a[MAXN];
int ans[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int f[MAXN][MAXK<<1];

inline void dfs1(reg int u,reg int father){
	f[u][0]^=a[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			for(reg int j=0;j<(k<<1);++j)
				f[u][(j+1)%(k<<1)]^=f[v][j];
		}
	}
	return;
}

inline void dfs2(reg int u,reg int father){
	for(reg int i=k;i<(k<<1);++i)
		ans[u]^=f[u][i];
	int g[MAXK<<1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			for(reg int j=0;j<(k<<1);++j)
				g[(j+1)%(k<<1)]=f[u][(j+1)%(k<<1)]^f[v][j];
			for(reg int j=0;j<(k<<1);++j)
				f[v][(j+1)%(k<<1)]^=g[j];
			dfs2(v,u);
		}
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	dfs1(1,0),dfs2(1,0);
	for(reg int i=1;i<=n;++i)
		putchar('0'|(bool)ans[i]),putchar(i==n?'\n':' ');
	flush();
	return 0;
}