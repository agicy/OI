#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int MAXM=500+5;

int n,m;
char M[MAXN][MAXM];

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

int dis[MAXN][MAXM];
deque<Node> Q;

inline void bfs(reg int sx,reg int sy){
	memset(dis,0x3f,sizeof(dis));
	dis[sx][sy]=0,Q.push_back(Node(sx,sy));
	while(!Q.empty()){
		static Node u;
		u=Q.front();
		Q.pop_front();
		reg int x=u.x,y=u.y;
		const int dx[]={-1,-1,1,1};
		const int dy[]={-1,1,-1,1};
		const int dcx[]={-1,-1,0,0};
		const int dcy[]={-1,0,-1,0};
		const char c[]={'\\','/','/','\\'};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			reg int a=x+dcx[i],b=y+dcy[i];
			reg int w=(M[a][b]!=c[i]);
			if(0<=fx&&fx<=n&&0<=fy&&fy<=m&&dis[fx][fy]>dis[x][y]+w){
				dis[fx][fy]=dis[x][y]+w;
				if(w)
					Q.push_back(Node(fx,fy));
				else
					Q.push_front(Node(fx,fy));
			}
		}
	}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=0;i<n;++i)
		scanf("%s",M[i]);
	bfs(0,0);
	if(dis[n][m]==0x3f3f3f3f)
		puts("NO SOLUTION");
	else
		printf("%d\n",dis[n][m]);
	return 0;
}