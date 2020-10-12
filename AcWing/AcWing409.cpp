#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=120+5;
const int MAXM=MAXN*(MAXN-1)/2;
const int MAXV=MAXN;
const int MAXE=MAXM;

int n,m;
int cnt,head[MAXV],to[MAXE],Next[MAXE];
bool vis[MAXV];
int mat[MAXV];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			vis[v]=true;
			if(!mat[v]||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	reg int T=read();
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		memset(mat,0,sizeof(mat));
		n=read(),m=read();
		for(reg int i=1;i<=m;++i){
			static int a,b;
			a=read(),b=read();
			Add_Edge(a,b);
		}
		reg int ans=0;
		for(reg int i=1;i<=n;++i){
			memset(vis,false,sizeof(vis));
			if(dfs(i))
				++ans;
		}
		printf("%d\n",n-ans);
	}
	return 0;
}