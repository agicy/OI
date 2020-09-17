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

const int MAXN=1e4+5;
const int MAXM=5e4+5;
const int MAXV=MAXN;
const int MAXE=MAXM*2;

int n,m;
int cnt=1,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int top,ans[MAXE];

inline void dfs(reg int u){
	for(reg int i=head[u];i;i=head[u]){
		reg int v=to[i];
		head[u]=Next[i];
		dfs(v);
	}
	ans[++top]=u;
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	dfs(1);
	for(reg int i=top;i>=1;--i)
		printf("%d\n",ans[i]);
	return 0;
}