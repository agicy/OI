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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int MAXM=100+5;
const int MAXV=MAXN*MAXM;
const int MAXE=MAXN*MAXM*4;
const int inf=0x3f3f3f3f;

int n,m;
char M[MAXN][MAXM];
int id[MAXN][MAXM];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int mat[MAXV];
int tim,vis[MAXV];

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(vis[v]==tim)
			continue;
		vis[v]=tim;
		if(!mat[v]||dfs(mat[v])){
			mat[v]=u;
			mat[u]=v;
			return true;
		}
	}
	return false;
}

bool chk[MAXV];

inline void dfs_ans(reg int u){
	chk[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!chk[mat[v]])
			dfs_ans(mat[v]);
	}
	return;
}

pair<int,int> ans[MAXV];

int main(void){
	n=read(),m=read();
	reg int Id=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			do
				M[i][j]=getchar();
			while(M[i][j]!='.'&&M[i][j]!='#');
			id[i][j]=++Id;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			if(M[i][j]=='#')
				continue;
			if(i<n&&M[i+1][j]=='.'){
				Add_Edge(id[i][j],id[i+1][j]);
				Add_Edge(id[i+1][j],id[i][j]);
			}
			if(j<m&&M[i][j+1]=='.'){
				Add_Edge(id[i][j],id[i][j+1]);
				Add_Edge(id[i][j+1],id[i][j]);
			}
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(((i+j)&1)&&M[i][j]=='.')
				++tim,dfs(id[i][j]);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='.'&&!mat[id[i][j]]&&!chk[id[i][j]])
				dfs_ans(id[i][j]);
	reg int tot=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(chk[id[i][j]])
				ans[++tot]=make_pair(i,j);
	printf("%d\n",tot);
	for(reg int i=1;i<=tot;++i)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}