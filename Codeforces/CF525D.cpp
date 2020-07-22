#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2000+5;
const int MAXM=2000+5;

struct Node{
	int x,y;
	inline Node(reg int X,reg int Y){
		x=X,y=Y;
		return;
	}
};

int n,m;
char M[MAXN][MAXM];
int c[MAXN][MAXM];
queue<Node> Q;

inline void Solve(void){
	static int b[4];
	while(!Q.empty()){
		reg int x=Q.front().x,y=Q.front().y;
		Q.pop();
		memset(b,0,sizeof(b));
		if(x!=1&&y!=1)
			b[0]=c[x-1][y-1]+c[x][y-1]+c[x-1][y];
		if(x!=1&&y!=m)
			b[1]=c[x-1][y+1]+c[x][y+1]+c[x-1][y];
		if(x!=n&&y!=m)
			b[2]=c[x+1][y+1]+c[x][y+1]+c[x+1][y];
		if(x!=n&&y!=1)
			b[3]=c[x+1][y-1]+c[x][y-1]+c[x+1][y];
		if(b[0]==1){
			if(c[x-1][y-1])
				c[x-1][y-1]=0,Q.push(Node(x-1,y-1));
			if(c[x][y-1])
				c[x][y-1]=0,Q.push(Node(x,y-1));
			if(c[x-1][y])
				c[x-1][y]=0,Q.push(Node(x-1,y));
		}
		if(b[1]==1){
			if(c[x-1][y+1])
				c[x-1][y+1]=0,Q.push(Node(x-1,y+1));
			if(c[x][y+1])
				c[x][y+1]=0,Q.push(Node(x,y+1));
			if(c[x-1][y])
				c[x-1][y]=0,Q.push(Node(x-1,y));
		}
		if(b[2]==1){
			if(c[x+1][y+1])
				c[x+1][y+1]=0,Q.push(Node(x+1,y+1));
			if(c[x][y+1])
				c[x][y+1]=0,Q.push(Node(x,y+1));
			if(c[x+1][y])
				c[x+1][y]=0,Q.push(Node(x+1,y));
		}
		if(b[3]==1){
			if(c[x+1][y-1])
				c[x+1][y-1]=0,Q.push(Node(x+1,y-1));
			if(c[x][y-1])
				c[x][y-1]=0,Q.push(Node(x,y-1));
			if(c[x+1][y])
				c[x+1][y]=0,Q.push(Node(x+1,y));
		}
	}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='.')
				Q.push(Node(i,j));
			else
				c[i][j]=1;
	Solve();
	for(reg int i=1;i<=n;++i,putchar('\n'))
		for(reg int j=1;j<=m;++j)
			if(c[i][j])
				putchar('*');
			else
				putchar('.');
	return 0;
}
