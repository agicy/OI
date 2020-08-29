#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=10+2;

int n,m;
int E[MAXN][MAXN][MAXN][MAXN];
int cnt[MAXN][MAXN];
int key[MAXN][MAXN][MAXN];
bool vis[MAXN][MAXN][1<<14];

struct Node{
	int x,y,k,d;
	inline Node(reg int x=0,reg int y=0,reg int k=0,reg int d=0):x(x),y(y),k(k),d(d){
		return;
	}
};

inline int getkey(reg int x,reg int y){
	reg int res=0;
	for(reg int i=1;i<=cnt[x][y];++i)
		res|=(1<<(key[x][y][i]-1));
	return res;
}

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=n&&1<=y&&y<=m;
}

queue<Node> Q;

inline int bfs(reg int sx,reg int sy){
	reg int sk=getkey(sx,sy);
	vis[sx][sy][sk]=true,Q.push(Node(sx,sy,sk,0));
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg int x=s.x,y=s.y,d=s.d,k=s.k;
		if(x==n&&y==m)
			return d;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(fx,fy)){
				reg int opt=E[x][y][fx][fy];
				if(opt<0)
					continue;
				if(opt&&!((k>>(opt-1))&1))
					continue;
				reg int fk=k|getkey(fx,fy);
				if(!vis[fx][fy][fk]){
					vis[fx][fy][fk]=true;
					Q.push(Node(fx,fy,fk,d+1));
				}
			}
		}
	}
	return -1;
}

int main(void){
	int k;
	scanf("%d%d%*d%d",&n,&m,&k);
	while(k--){
		static int x1,y1,x2,y2,g;
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&g);
		if(g)
			E[x1][y1][x2][y2]=E[x2][y2][x1][y1]=g;
		else
			E[x1][y1][x2][y2]=E[x2][y2][x1][y1]=-1;
	}
	int s;
	scanf("%d",&s);
	while(s--){
		static int x,y,q;
		scanf("%d%d%d",&x,&y,&q);
		key[x][y][++cnt[x][y]]=q;
	}
	printf("%d\n",bfs(1,1));
}