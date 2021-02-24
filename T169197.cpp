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

const int mod=1e8+7;

const int MAXN=20;
const int MAXM=20;

int n,m;
int row[MAXN][MAXM],clu[MAXN][MAXM];

namespace Subtask1{
	bool cover[MAXN][MAXM];
	inline bool check(reg int x,reg int y){
		return 0<=x&&x<n&&0<=y&&y<m&&!cover[x][y];
	}
	inline bool isNoStone(reg int x,reg int y,reg int dx,reg int dy){
		if(dx)
			if(dx<0)
				return clu[x+dx][y];
			else
				return clu[x][y];
		else
			if(dy<0)
				return row[x][y+dy];
			else
				return row[x][y];
	}
	int ans;
	inline void check(void){
		++ans;
		return;
	}
	inline void dfs(reg int x,reg int y){
		if(x==n){
			check();
			return;
		}
		if(cover[x][y]){
			if(y+1==m)
				dfs(x+1,0);
			else
				dfs(x,y+1);
			return;
		}
		// *****
		// *****
		// *****
		// |---|
		// *---*
		if(check(x+1,y)&&isNoStone(x,y,+1,0)){
			cover[x][y]=cover[x+1][y]=1;
			if(y+1==m)
				dfs(x+1,0);
			else
				dfs(x,y+1);
			cover[x][y]=cover[x+1][y]=0;
		}
		// *****---*
		// *****---|
		// *****---*
		if(check(x,y+1)&&isNoStone(x,y,0,+1)){
			cover[x][y]=cover[x][y+1]=2;
			if(y+1==m)
				dfs(x+1,0);
			else
				dfs(x,y+1);
			cover[x][y]=cover[x][y+1]=0;
		}
		// *****---*
		// *****---|
		// *****---*
		// |---|
		// *---*
		if(check(x,y+1)&&isNoStone(x,y,0,+1)&&check(x+1,y)&&isNoStone(x,y,+1,0)){
			cover[x][y]=cover[x][y+1]=cover[x+1][y]=3;
			if(y+1==m)
				dfs(x+1,0);
			else
				dfs(x,y+1);
			cover[x][y]=cover[x][y+1]=cover[x+1][y]=0;
		}
		//     *---*
		//     |---|
		// *---*****
		// |---*****
		// *---*****
		if(check(x,y-1)&&isNoStone(x,y,0,-1)&&check(x-1,y)&&isNoStone(x,y,-1,0)){
			cover[x][y]=cover[x][y-1]=cover[x-1][y]=4;
			if(y+1==m)
				dfs(x+1,0);
			else
				dfs(x,y+1);
			cover[x][y]=cover[x][y-1]=cover[x-1][y]=0;
		}
		if(y+1==m)
			dfs(x+1,0);
		else
			dfs(x,y+1);
		return;
	}
	inline void Solve(void){
		dfs(0,0);
		printf("%d\n",ans%mod);
		return;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m-1;++j)
			row[i][j]=read();
	for(reg int i=0;i<n-1;++i)
		for(reg int j=0;j<m;++j)
			clu[i][j]=read();
	Subtask1::Solve();
	return 0;
}