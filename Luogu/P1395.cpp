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

const int MAXN=5e4+5;
const int inf=0x3f3f3f3f;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int f[MAXN];
int siz[MAXN];

inline void dfs(reg int u,reg int father,reg int dis){
	f[1]+=dis;
	siz[u]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u,dis+1);
			siz[u]+=siz[v];
		}
	}
	return;
}

int Min=inf,ptr=-1;

inline void dp(reg int u,reg int father){
	if(f[u]<Min||(f[u]==Min&&u<ptr))
		Min=f[u],ptr=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			f[v]=f[u]-siz[v]+n-siz[v];
			dp(v,u);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	dfs(1,0,0);
	dp(1,0);
	printf("%d %d\n",ptr,Min);
	return 0;
}