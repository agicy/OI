#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXH=100+5;
const int MAXW=100+5;

int H,W;
char M[MAXH][MAXW];

struct Node{
	int x,y,dis;
	inline Node(reg int x=0,reg int y=0,reg int dis=0):x(x),y(y),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXH][MAXW];
int dis[MAXH][MAXW];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=H&&1<=y&&y<=W;
}

inline void BFS(void){
	const int dx[]={-1,0,0,1};
	const int dy[]={0,-1,1,0};
	memset(dis,0X3F,sizeof(dis));
	dis[1][1]=(M[1][1]=='#'),Q.push(Node(1,1,dis[1][1]));
	while(!Q.empty()){
		static Node u;
		u=Q.top();
		Q.pop();
		reg int x=u.x,y=u.y;
		if(vis[x][y])
			continue;
		vis[x][y]=true;
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(fx,fy)&&dis[fx][fy]>dis[x][y]+(M[fx][fy]=='#')){
				dis[fx][fy]=dis[x][y]+(M[fx][fy]=='#');
				Q.push(Node(fx,fy,dis[fx][fy]));
			}
		}
	}
	return;
}

int main(void){
	scanf("%d%d",&H,&W);
	for(reg int i=1;i<=H;++i)
		scanf("%s",M[i]+1);
	BFS();
	reg int ans=dis[H][W];
	printf("%d\n",ans);
	return 0;
}