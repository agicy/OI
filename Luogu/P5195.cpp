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

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXW=1e3+5;
const int MAXH=1e3+5;
const int inf=0x3f3f3f3f;

int w,h;
int M[MAXW][MAXH];
bool vis[2][MAXW][MAXH];
int dis[2][MAXW][MAXH];

queue<int> Qx,Qy;

inline void bfs(reg int id,int sx,int sy){
	vis[id][sx][sy]=true,dis[id][sx][sy]=0,Qx.push(sx),Qy.push(sy);
	while(!Qx.empty()){
		reg int x=Qx.front(),y=Qy.front();
		Qx.pop(),Qy.pop();
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			int fx=x+dx[i],fy=y+dy[i];
			if(1<=fx&&fx<=h&&1<=fy&&fy<=w&&M[fx][fy]!=1&&!vis[id][fx][fy]){
				if(!id&&M[fx][fy]==3)
					continue;
				vis[id][fx][fy]=true;
				dis[id][fx][fy]=dis[id][x][y]+1;
				Qx.push(fx),Qy.push(fy);
			}
		}
	}
	return;
}

int main(void){
	w=read(),h=read();
	reg int sx=-1,sy=-1,ex=-1,ey=-1;
	for(reg int i=1;i<=h;++i)
		for(reg int j=1;j<=w;++j){
			M[i][j]=read();
			switch(M[i][j]){
				case 2:{
					sx=i,sy=j;
					break;
				}
				case 3:{
					ex=i,ey=j;
					break;
				}
			}
		}
	memset(dis,0x3f,sizeof(dis));
	bfs(0,sx,sy),bfs(1,ex,ey);
	int ans=inf;
	for(reg int i=1;i<=h;++i)
		for(reg int j=1;j<=w;++j)
			if(M[i][j]==4)
				cMin(ans,dis[0][i][j]+dis[1][i][j]);
	printf("%d\n",ans);
	return 0;
}