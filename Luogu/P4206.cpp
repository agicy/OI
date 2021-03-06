#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e3+5;

int n,e,c,m;
vector<int> G[MAXN];
int dir[MAXN][MAXN],dep[MAXN][MAXN];
double f[MAXN][MAXN];

inline double dp(reg int x,reg int y){
	if(x==y)
		return 0;
	if(dir[x][y]==y||dir[dir[x][y]][y]==y)
		return 1;
	if(f[x][y]!=0.0)
		return f[x][y];
	reg double res=dp(dir[dir[x][y]][y],y);
	for(int v:G[y])
		res+=dp(dir[dir[x][y]][y],v);
	return f[x][y]=res/(G[y].size()+1)+1;
}

int main(void){
	n=read(),e=read(),c=read(),m=read();
	for(reg int i=1;i<=e;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	memset(dep,-1,sizeof(dep));
	for(reg int i=1;i<=n;++i){
		reg int _head=0,_tail=0;
		static int Q[MAXN];
		dep[i][i]=0,Q[_tail++]=i;
		while(_head<_tail){
			reg int u=Q[_head++];
			for(int v:G[u])
				if(dep[i][v]==-1){
					dep[i][v]=dep[i][u]+1;
					Q[_tail++]=v;
				}
		}
	}
	memset(dir,0x3f,sizeof(dir));
	for(reg int i=1;i<=n;++i)
		for(int v:G[i])
			for(reg int j=1;j<=n;++j)
				if(dep[i][j]==dep[v][j]+1)
					dir[i][j]=min(dir[i][j],v);
	printf("%.3lf\n",dp(c,m));
	return 0;
}