#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F

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

Node box,person,en;

const int dx[]={-1,1,0,0};
const int dy[]={0,0,-1,1};

inline bool check(const Node& a){
	if(a.x<1||n<a.x||a.y<1||m<a.y)
		return false;
	if(M[a.x][a.y]=='#')
		return false;
	return true;
}

inline int expand(Node st,Node en,Node c){
	int f[MAXN][MAXM];
	queue<Node> Q;
	memset(f,-1,sizeof(f));
	while(!Q.empty())
		Q.pop();
	Q.push(st);
	f[st.x][st.y]=0;
	while(!Q.empty()){
		Node temp=Q.front();
		reg int x=temp.x,y=temp.y;
		Q.pop();
		if(temp==en){
			return f[x][y];
		}
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(Node(fx,fy))&&f[fx][fy]==-1&&Node(fx,fy)!=c){
				f[fx][fy]=f[x][y]+1;
				Q.push(Node(fx,fy));
			}
		}
	}
	return INF;
}

inline void BFS(void){
	return;
}

int n,m;


int main(void){
	while(scanf("%d%d",&n,&m)!=EOF&&n!=0&&m!=0){
		Init();
		for(reg int i=1;i<=n;++i)
			scanf("%s",M[i]+1);
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j){
				switch(M[i][j]){
					case 'T':
						M[i][j]='.';
						en=Node(i,j);
						break;
					case 'S':
						M[i][j]='.';
						person=Node(i,j);
						break;
					case 'B':
						M[i][j]='.';
						box=Node(i,j);
						break;
					default:
						break;
				}
			}
		BFS();
	}
	return 0;
}

