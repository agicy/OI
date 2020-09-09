#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50+5;
const int MAXM=50+5;

int n,m;
int p[MAXN][MAXM];
bool vis[MAXN][MAXM];
int siz[MAXN][MAXM];
queue<int> Qx,Qy;

inline void bfs(int sx,int sy){
	vis[sx][sy]=true;
	Qx.push(sx),Qy.push(sy);
	while(!Qx.empty()){
		reg int x=Qx.front(),y=Qy.front();
		++siz[sx][sy];
		const int dx[]={0,-1,0,1};
		const int dy[]={-1,0,1,0};
		for(reg int i=0;i<4;++i){
			int fx=x+dx[i],fy=y+dy[i];
			if((p[x][y]>>i)&1)
				continue;
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!vis[fx][fy]){
				vis[fx][fy]=true;
				Qx.push(fx),Qy.push(fy);
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			p[i][j]=read();
	puts("SDASD");
	reg int cnt=0;
	int Max=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			if(!vis[i][j]){
				++cnt;
				bfs(i,j);
				Max=max(Max,siz[i][j]);
			}
		}
	printf("%d\n%d\n",cnt,Max);
	return 0;
}