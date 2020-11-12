#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;
const int MAXM=2e3+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int col[MAXN];

inline void dfs1(reg int u,reg int c){
	col[u]=c;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!col[v])
			dfs1(v,c^2);
	}
	return;
}

bool vis[MAXN];
int mat[MAXN];

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
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read()+1,y=read()+1;
		Add_Edge(x,y),Add_Edge(y,x);
	}
	for(reg int i=1;i<=n;++i)
		if(!col[i])
			dfs1(i,1);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i){
		if(col[i]!=1)
			continue;
		for(reg int j=1;j<=n;++j)
			vis[j]=false;
		if(dfs(i))
			++cnt;
	}
	printf("%d\n",n-cnt);
	return 0;
}