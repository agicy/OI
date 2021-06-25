#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,m;
vector<int> G[MAXN];
bool vis[MAXN];
int col[MAXN];

inline bool dfs(reg int u,reg int c){
	vis[u]=true;
	col[u]=c;
	reg bool flag=true;
	for(int v:G[u]){
		if(!vis[v])
			flag&=dfs(v,c^1);
		else if(col[u]==col[v])
			flag=false;
	}
	return flag;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	reg int A=0,B=0,C=0;
	fill(col+1,col+n+1,-1);
	for(reg int i=1;i<=n;++i)
		if(!vis[i]){
			if(!G[i].size())
				++C;
			else
				dfs(i,0)?++B:++A;
		}
	printf("%lld\n",A+1ll*A*(A-1)+2*B+2ll*B*(A+B-1)+C+1ll*C*(2*n-C-1));
	return 0;
}