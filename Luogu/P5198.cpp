#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e3+5;

int n;
bool M[MAXN][MAXN];
bool vis[MAXN][MAXN];
int ans1,ans2;

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

Node Q[MAXN*MAXN];

inline void bfs(reg int sx,reg int sy){
	reg int S=0,C=0;
	reg int head=0,tail=0;
	vis[sx][sy]=true,Q[tail++]=Node(sx,sy);
	while(head<tail){
		static Node s;
		s=Q[head++];
		reg int x=s.x,y=s.y;
		++S;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(!M[fx][fy])
				++C;
			else if(1<=fx&&fx<=n&&1<=fy&&fy<=n&&!vis[fx][fy]){
				vis[fx][fy]=true;
				Q[tail++]=Node(fx,fy);
			}
		}
	}
	if(S>ans1)
		ans1=S,ans2=C;
	else if(S==ans1&&C<ans2)
		ans2=C;
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			static char ch;
			do
				ch=getchar();
			while(ch!='.'&&ch!='#');
			M[i][j]=(ch=='#');
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(M[i][j]&&!vis[i][j])
				bfs(i,j);
	printf("%d %d\n",ans1,ans2);
	return 0;
}