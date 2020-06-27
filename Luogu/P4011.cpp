#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

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
	for(int i=1;i<=cnt[x][y];++i)
		res|=(1<<(key[x][y][i]-1));
	return res;
}

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=n&&1<=y&&y<=m;
}

queue<Node> Q;

inline int BFS(reg int sx,reg int sy){
	reg int sk=getkey(sx,sy);
	vis[sx][sy][sk]=true,Q.push(Node(sx,sy,sk,0));
	while(!Q.empty()){
		static Node S;
		S=Q.front();
		Q.pop();
		reg int x=S.x,y=S.y,d=S.d,k=S.k;
		if(x==n&&y==m)
			return d;
		const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
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
	n=read(),m=read(),read();
	reg int k=read();
	while(k--){
		static int x1,y1,x2,y2,g;
		x1=read(),y1=read(),x2=read(),y2=read(),g=read();
		if(g)
			E[x1][y1][x2][y2]=E[x2][y2][x1][y1]=g;
		else
			E[x1][y1][x2][y2]=E[x2][y2][x1][y1]=-1;
	}
	reg int s=read();
	while(s--){
		static int x,y,Q;
		x=read(),y=read(),Q=read();
		key[x][y][++cnt[x][y]]=Q;
	}
	printf("%d\n",BFS(1,1));
	return 0;
}