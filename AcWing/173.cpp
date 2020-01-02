#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=1000+5;
const int MAXM=1000+5;

int n,m;

struct Node{
	int x,y,t;
	inline Node(void){
		x=y=t=0;
		return;
	}
	inline Node(reg int a,reg int b,reg int c){
		x=a,y=b,t=c;
	}
};

bool vis[MAXN][MAXM];
int ans[MAXN][MAXM];
queue<Node> Q;

inline void BFS(void){
	const int fx[]={-1,0,0,1},fy[]={0,-1,1,0};
	Node temp;
	while(!Q.empty()){
		temp=Q.front();
		Q.pop();
		for(reg int i=0;i<4;++i){
			reg int dx=temp.x+fx[i],dy=temp.y+fy[i];
			if(1<=dx&&dx<=n&&1<=dy&&dy<=m&&!vis[dx][dy]){
				vis[dx][dy]=true;
				ans[dx][dy]=temp.t+1;
				Q.push(Node(dx,dy,ans[dx][dy]));
			}
		}
	}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			static int x;
			scanf("%1d",&x);
			if(x){
				vis[i][j]=true;
				Q.push(Node(i,j,0));
			}
		}
	BFS();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			printf("%d%c",ans[i][j],j==m?'\n':' ');
	return 0;
}
