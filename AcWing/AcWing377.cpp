#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50+5;
const int MAXM=50+5;
const int MAXV=MAXN*MAXM*2;
const int MAXE=MAXN*MAXM;

int n,m;
char M[MAXN][MAXM];
int id1[MAXN][MAXM],id2[MAXN][MAXM];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXV];
int mat[MAXV];

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			vis[v]=true;
			if(!mat[v]||dfs(mat[v])){
				mat[u]=v;
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	reg int cnt1=0,cnt2=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='*'){
				if(M[i][j-1]=='*')
					id1[i][j]=id1[i][j-1];
				else
					id1[i][j]=++cnt1;
				if(M[i-1][j]=='*')
					id2[i][j]=id2[i-1][j];
				else
					id2[i][j]=++cnt2;
			}
	reg int tmp=n*m;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			Add_Edge(id1[i][j],id2[i][j]+tmp);
	reg int ans=0;
	for(reg int i=1;i<=cnt1;++i)
		if(!mat[i]){
			memset(vis,false,sizeof(vis));
			if(dfs(i))
				++ans;
		}
	printf("%d\n",ans);
	return 0;
}