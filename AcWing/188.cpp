#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=150+5;
const int MAXM=150+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
char M[MAXN][MAXM];

inline void Read(void){
	scanf("%d%d\n",&m,&n);
	for(reg int i=1;i<=n;++i)
		scanf("%s\n",M[i]+1);
	return;
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

queue<Node> Q;

int f[MAXN][MAXM];

inline bool check(const Node& a){
	if(a.x<1||n<a.x||a.y<1||m<a.y)
		return false;
	if(f[a.x][a.y]!=-1)
		return false;
	if(M[a.x][a.y]!='*')
		return true;
	else
		return false;
}

inline void BFS(const Node& s){
	memset(f,-1,sizeof(f));
	while(!Q.empty())
		Q.pop();
	f[s.x][s.y]=0;
	Q.push(s);
	while(!Q.empty()){
		static Node temp;
		temp=Q.front();
		Q.pop();
		reg int x=temp.x,y=temp.y;
		if(M[x][y]=='H'){
			printf("%d\n",f[x][y]);
			exit(0);
		}
		const int 
			dx[]={-2,-2,-1,-1,+1,+1,+2,+2},
			dy[]={-1,+1,-2,+2,-2,+2,-1,+1};
		for(reg int i=0;i<8;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(Node(fx,fy))){
				f[fx][fy]=f[x][y]+1;
				Q.push(Node(fx,fy));
			}
		}
	}
	return;
}

Node st;

inline void FindS(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='K'){
				st=Node(i,j);
				return;
			}
	return;
}

inline void Work(void){
	FindS();
	BFS(st);
	return;
}
