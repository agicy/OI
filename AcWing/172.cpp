#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F

const int MAXN=500+5;
const int MAXM=500+5;

const int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};

const int Next_x[3][4]={
0,0,-2,1,
0,0,-1,1,
0,0,-1,2
};

const int Next_y[3][4]={
-2,1,0,0,
-1,2,0,0,
-1,1,0,0
};

const int Next_lie[3][4]={
1,1,2,2,
0,0,1,1,
2,2,0,0
};

struct Node{
	int x,y,s;
	inline Node(void){
		x=y=s=0;
		return;
	}
	inline Node(reg int a,reg int b,reg int c){
		x=a,y=b,s=c;
		return;
	}
	inline bool operator==(const Node& a)const{
		return x==a.x&&y==a.y&&s==a.s;
	}
};

struct Map{
	int dis[MAXN][MAXM][3];
	inline void Init(void){
		memset(dis,0X3F,sizeof(dis));
		return;
	}
	inline int& operator[](const Node& a){
		return dis[a.x][a.y][a.s];
	}
};

int n,m;
char M[MAXN][MAXM];
Map dis;
Node s,e;
queue<Node> Q;

inline bool check(reg int i,reg int j){
	return 1<=i&&i<=n&&1<=j&&j<=m;
}

inline void GetSE(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='O')
				M[i][j]='.',e=Node(i,j,0);
			else if(M[i][j]=='X'){
				for(reg int k=0,x,y;(k<4)&&(x=i+dx[k],y=j+dy[k],true);++k)
					if(check(x,y)&&M[x][y]=='X'){
						M[i][j]=M[x][y]='.',s=Node(min((int)i,(int)x),min((int)j,(int)y),k<2?1:2);
						break;
					}
					else if(M[i][j]=='X')
						M[i][j]='.',s=Node(i,j,0);
			}
	return;
}

inline bool check(const Node& a){
	if(!check(a.x,a.y)||(M[a.x][a.y]=='#')||(a.s==0&&M[a.x][a.y]!='.')||(a.s==1&&M[a.x][a.y+1]=='#')||(a.s==2&&M[a.x+1][a.y]=='#'))
		return false;
	else
		return true;
}

inline void BFS(void){
	while(!Q.empty())Q.pop();
	dis.Init(),dis[s]=0,Q.push(s);
	while(!Q.empty()){
		static Node now,Next;
		now=Q.front(),Q.pop();
		for(reg int i=0;i<4;++i)
			if(Next=Node(now.x+Next_x[now.s][i],now.y+Next_y[now.s][i],Next_lie[now.s][i]),check(Next)&&dis[Next]==INF)
				if(dis[Next]=dis[now]+1,Q.push(Next),Next==e)
					return;
	}
	return ;
}

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF&&n!=0&&m!=0){
		for(reg int i=1;i<=n;++i)
			scanf("%s",M[i]+1);
		if(GetSE(),BFS(),dis[e]==INF)
			puts("Impossible");
		else
			printf("%d\n",dis[e]);
	}
	return 0;
}
