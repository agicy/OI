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

const int MAXN=100+5;
const int MAXM=100+5;

bool G[MAXN][MAXM];
bool vis[MAXN][MAXM];
int n,m,t;
pair<int,int> mat[MAXN][MAXM];

inline bool dfs(int x,int y){
	const int dx[]={-2,-2,2,2,-1,-1,1,1};
	const int dy[]={-1,1,-1,1,-2,2,-2,2};
	for(reg int i=0;i<8;++i){
		reg int fx=x+dx[i],fy=y+dy[i];
		if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!G[fx][fy]&&!vis[fx][fy]){
			static pair<int,int> p;
			vis[fx][fy]=true;
			p=mat[fx][fy];
			if((!p.first&&!p.second)||dfs(p.first,p.second)){
				mat[fx][fy]=make_pair(x,y);
				return true;
			}
		}
	}
	return false;
}

int main(void){
	n=read(),m=read(),t=read();
	for(reg int i=1;i<=t;++i){
		static int x,y;
		x=read(),y=read();
		G[x][y]=true;
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			if(G[i][j]||((i+j)&1))
				continue;
			memset(vis,false,sizeof(vis));
			if(dfs(i,j))
				++ans;
		}
	printf("%d\n",n*m-t-ans);
	return 0;
}