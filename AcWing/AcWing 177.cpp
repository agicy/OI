#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=800+5;
const int MAXM=800+5;

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		Init();
		Read();
		Work();
	}
	return 0;
}

struct Node{
	int x,y;
	inline Node(void){
		x=y=0;
		return;
	}
	inline Node(reg int a,reg int b){
		x=a,y=b;
		return;
	}
};

bool flag;
int n,m;
char M[MAXN][MAXM];
queue<Node> Boy,Girl;
int cnt;
Node G[2];
int t;
bool vis1[MAXN][MAXM],vis2[MAXN][MAXM];

inline void Init(void){
	flag=false;
	t=cnt=0;
	memset(vis1,false,sizeof(vis1));
	memset(vis2,false,sizeof(vis2));
	while(!Boy.empty())
		Boy.pop();
	while(!Girl.empty())
		Girl.pop();
	return;
}

inline void Read(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			cin>>M[i][j];
			switch(M[i][j]){
				case 'M':
					Boy.push(Node(i,j));
					break;
				case 'G':
					Girl.push(Node(i,j));
					break;
				case 'Z':
					G[cnt++]=Node(i,j);
					break;
				default:
					break;
			}
		}
	return;
}

inline bool check(reg int x,reg int y){
	return !((x<1||n<x||y<1||m<y)||(M[x][y]=='X')||(abs(G[0].x-x)+abs(G[0].y-y)<=2*t)||(abs(G[1].x-x)+abs(G[1].y-y)<=2*t));
}

inline void BFS(queue<Node>& Q,reg bool vis1[MAXN][MAXM],reg bool vis2[MAXN][MAXM]){
	reg int size=Q.size();
	for(reg int i=1;i<=size;++i){
		static Node temp;
		temp=Q.front();
		Q.pop();
		reg int x=temp.x,y=temp.y;
		if(!check(x,y))
			continue;
		static int fx[]={-1,0,0,1},fy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int dx=x+fx[i],dy=y+fy[i];
			if(check(dx,dy)&&!vis1[dx][dy]){
				vis1[dx][dy]=true;
				if(vis2[dx][dy]){
					flag=true;
					break;
				}
				Q.push(Node(dx,dy));
			}
		}
	}
	return;
}

inline void Work(void){
	while(!Boy.empty()||!Girl.empty()){
		++t;
		BFS(Boy,vis1,vis2);
		BFS(Boy,vis1,vis2);
		BFS(Boy,vis1,vis2);
		BFS(Girl,vis2,vis1);
		if(flag){
			printf("%d\n",t);
			return;
		}
	}
	puts("-1");
	return;
}
