#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s!='|'&&*s!='-'&&*s!='.'&&*s!='#'&&*s!='/'&&*s!='\\')*s=getchar();
	while(*s=='|'||*s=='-'||*s=='.'||*s=='#'||*s=='/'||*s=='\\')*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=50+5;
const int MAXM=50+5;
const int MAXCNT=MAXN*MAXM;
const int MAXV=2*MAXCNT;

int n,m;
char M[MAXN][MAXN];

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=n&&1<=y&&y<=m&&M[x][y]!='#';
}

inline bool tower(reg int x,reg int y){
	return M[x][y]=='|'||M[x][y]=='-';
}

inline bool dfs(reg bool V[MAXN][MAXM],reg int x,reg int y,reg int dir){
	V[x][y]=true;
	const int dx[]={-1,0,1,0};
	const int dy[]={0,1,0,-1};
	reg int fx=x+dx[dir],fy=y+dy[dir];
	if(!check(fx,fy))
		return true;
	if(tower(fx,fy))
		return false;
	if(M[fx][fy]=='.')
		return dfs(V,fx,fy,dir);
	else
		return dfs(V,fx,fy,dir^(M[fx][fy]=='/'?1:3));
}

bool covH[MAXN][MAXM];

inline bool getH(reg int x,reg int y){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			covH[i][j]=false;
	reg bool flag1=dfs(covH,x,y,1),flag2=dfs(covH,x,y,3);
	return flag1&&flag2;
}

bool covV[MAXN][MAXM];

inline bool getV(reg int x,reg int y){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			covV[i][j]=false;
	reg bool flag1=dfs(covV,x,y,0),flag2=dfs(covV,x,y,2);
	return flag1&&flag2;
}

vector<int> G[MAXV];
bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int scc_cnt,col[MAXV];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=0,siz=G[u].size();i<siz;++i){
		reg int v=G[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		reg int v;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(v!=u);
	}
	return;
}

bool tag[MAXN][MAXM];
int id[MAXN][MAXM];
vector<int> V[MAXN][MAXM];

inline void solve(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	memset(tag,false,sizeof(tag));
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			V[i][j].clear();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(tower(i,j)){
				id[i][j]=++tot;
				reg bool tagH=getH(i,j),tagV=getV(i,j);
				if(!tagH&&!tagV){
					writeln("IMPOSSIBLE");
					return;
				}
				else if(!tagH){
					for(reg int x=1;x<=n;++x)
						for(reg int y=1;y<=m;++y)
							if(M[x][y]=='.'&&covV[x][y])
								V[x][y].push_back(tot<<1|1);
					G[tot<<1].push_back(tot<<1|1);
				}
				else if(!tagV){
					for(reg int x=1;x<=n;++x)
						for(reg int y=1;y<=m;++y)
							if(M[x][y]=='.'&&covH[x][y])
								V[x][y].push_back(tot<<1);
					G[tot<<1|1].push_back(tot<<1);
				}
				else{
					for(reg int x=1;x<=n;++x)
						for(reg int y=1;y<=m;++y)
							if(M[x][y]=='.'){
								if(covH[x][y]&&covV[x][y])
									tag[x][y]=true;
								else if(covH[x][y])
									V[x][y].push_back(tot<<1);
								else if(covV[x][y])
									V[x][y].push_back(tot<<1|1);
							}
				}
			}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='.'&&!tag[i][j])
				switch(V[i][j].size()){
					case 0:{
						writeln("IMPOSSIBLE");
						return;
					}
					case 1:{
						G[V[i][j][0]^1].push_back(V[i][j][0]);
						break;
					}
					case 2:{
						G[V[i][j][0]^1].push_back(V[i][j][1]),G[V[i][j][1]^1].push_back(V[i][j][0]);
						break;
					}
				}
	tim=0,memset(dfn,0,sizeof(dfn)),scc_cnt=0;
	for(reg int i=1;i<=tot;++i){
		if(!dfn[i<<1])
			tarjan(i<<1);
		if(!dfn[i<<1|1])
			tarjan(i<<1|1);
	}
	for(reg int i=1;i<=tot;++i)
		if(col[i<<1]==col[i<<1|1]){
			writeln("IMPOSSIBLE");
			return;
		}
	for(reg int i=1;i<=tot;++i)
		G[i<<1].clear(),G[i<<1|1].clear();
	writeln("POSSIBLE");
	for(reg int i=1;i<=n;++i,putchar('\n'))
		for(reg int j=1;j<=m;++j)
			if(!tower(i,j))
				putchar(M[i][j]);
			else
				putchar(col[id[i][j]<<1]<col[id[i][j]<<1|1]?'-':'|');
	return;
}

int main(void){
	reg int t=read();
	while(t--)
		solve();
	flush();
	return 0;
}