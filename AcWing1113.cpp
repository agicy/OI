#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXH=20+5;
const int MAXW=20+5;

int w,h;
char M[MAXH][MAXW];
int ans;
bool vis[MAXH][MAXW];
queue<int> Qx,Qy;

inline void bfs(reg int sx,reg int sy){
	vis[sx][sy]=true;
	Qx.push(sx),Qy.push(sy);
	while(!Qx.empty()){
		reg int x=Qx.front(),y=Qy.front();
		Qx.pop(),Qy.pop();
		++ans;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(1<=fx&&fx<=h&&1<=fy&&fy<=w&&!vis[fx][fy]&&M[fx][fy]!='#'){
				vis[fx][fy]=true;
				Qx.push(fx),Qy.push(fy);
			}
		}
	}
	return;
}

int main(void){
	while(scanf("%d%d",&w,&h)!=EOF){
		if(!w&&!h)
			break;
		for(reg int i=1;i<=h;++i)
			scanf("%s",M[i]+1);
		reg int sx=0,sy=0;
		for(reg int i=1;i<=h;++i)
			for(reg int j=1;j<=w;++j)
				if(M[i][j]=='@')
					sx=i,sy=j,M[i][j]='#';
		ans=0;
		memset(vis,false,sizeof(vis));
		bfs(sx,sy);
		printf("%d\n",ans);
	}
	return 0;
}