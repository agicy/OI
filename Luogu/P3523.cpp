#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=300000+5;

int n,m;
int Key[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tot;
int f[MAXN],g[MAXN];

inline void DFS(reg int u,reg int father,reg int dis){
	f[u]=INF,g[u]=-INF;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			DFS(v,u,dis);
			f[u]=min(f[u],f[v]+1),g[u]=max(g[u],g[v]+1);
		}
	}
	if(Key[u]&&f[u]>dis)
		g[u]=max(g[u],0);
	if(g[u]+f[u]<=dis)
		g[u]=-INF;
	if(g[u]==dis)
		++tot,g[u]=-INF,f[u]=0;
	return;
}

inline bool check(int mid){
	tot=0;
	DFS(1,0,mid);
	tot+=(g[1]>=0);
	return tot<=m;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		Key[i]=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	reg int l=0,r=n,mid,ans;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid-1,ans=mid;
		else
			l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}