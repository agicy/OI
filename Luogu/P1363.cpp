#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1500+5;
const int MAXM=1500+5;

inline void Read(void);
inline void Work(void);

int n,m;

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		Read();
		Work();
	}
	return 0;
}

int sx,sy;
char M[MAXN][MAXM];

inline void Read(void){
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j){
			cin>>M[i][j];
			if(M[i][j]=='S'){
				sx=i,sy=j;
				M[i][j]='.';
			}
		}
	return;
}

bool flag;
bool vis[MAXN][MAXM];
int Rx[MAXN][MAXM];
int Ry[MAXN][MAXM];

inline void DFS(reg int x,reg int y,reg int tx,reg int ty){
	if(flag)
		return;
	if(vis[x][y]&&(Rx[x][y]!=tx||Ry[x][y]!=ty)){
		flag=true;
		return;
	}
	vis[x][y]=true,Rx[x][y]=tx,Ry[x][y]=ty;
	const int dx[]={-1,0,0,1};
	const int dy[]={0,-1,1,0};
	for(reg int i=0;i<4;++i){
		reg int fx=(x+dx[i]+n)%n,fy=(y+dy[i]+m)%m;
		reg int flx=tx+dx[i],fly=ty+dy[i];
		if(M[fx][fy]=='.')
			if(Rx[fx][fy]!=flx||Ry[fx][fy]!=fly||!vis[fx][fy])
				DFS(fx,fy,flx,fly);
	}
	return;
}

inline void Work(void){
	flag=false;
	memset(vis,false,sizeof(vis));
	memset(Rx,0,sizeof(Rx));
	memset(Ry,0,sizeof(Ry));
	DFS(sx,sy,sx,sy);
	puts(flag?"Yes":"No");
	return;
}
