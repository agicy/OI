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

const int MAXN=5e5+5;
const double eps=1e-5;

int n;
int a[MAXN];
int deg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

double val[MAXN];

inline void DFS(reg int u,reg int father,reg double ans){
	val[u]=ans+log(a[u]);
	--deg[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			DFS(v,u,ans+log(deg[u]));
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		++deg[a],++deg[b];
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	++deg[1];
	DFS(1,0,0);
	val[n+1]=1e18;
	sort(val+1,val+n+1);
	int Max=0,cnt=1;
	for(reg int i=2;i<=n+1;++i)
		if(val[i]-val[i-1]<eps)
			++cnt;
		else
			Max=max(Max,cnt),cnt=1;
	printf("%d\n",n-Max);
	return 0;
}