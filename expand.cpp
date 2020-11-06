#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=300+5;
const int MAXM=300+5;
const int inf=0x3f3f3f3f;

int n,m,s;
int M[MAXN][MAXM];
int le[MAXN][MAXM],up[MAXN][MAXM],dn[MAXN][MAXM],ri[MAXN][MAXM];
int val[MAXN][MAXM];

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

int dis[MAXN][MAXM],sum[MAXN][MAXM];
queue<Node> Q;

inline void bfs(reg int sx,reg int sy){
	memset(dis,0x3f,sizeof(dis));
	dis[sx][sy]=0,sum[sx][sy]=val[sx][sy];
	Q.push(Node(sx,sy));
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg int x=s.x,y=s.y;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!M[fx][fy]){
				if(dis[fx][fy]>dis[x][y]+1){
					dis[fx][fy]=dis[x][y]+1,sum[fx][fy]=sum[x][y]+val[fx][fy];
					Q.push(Node(fx,fy));
				}
				else if(dis[fx][fy]==dis[x][y]+1&&sum[fx][fy]<sum[x][y]+val[fx][fy]){
					sum[fx][fy]=sum[x][y]+val[fx][fy];
					Q.push(Node(fx,fy));
				}
			}
		}
	}
	return;
}

int main(void){
	//freopen("expand.in","r",stdin);
	//freopen("expand.out","w",stdout);

	n=read(),m=read(),s=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			M[i][j]=read();
	for(reg int i=1;i<=n;++i)
		M[i][0]=M[i][m+1]=1;
	for(reg int i=1;i<=m;++i)
		M[0][i]=M[n+1][i]=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			if(M[i][j-1])
				le[i][j]=0;
			else
				le[i][j]=le[i][j-1]+1;
			if(M[i-1][j])
				up[i][j]=0;
			else
				up[i][j]=up[i-1][j]+1;
		}
	for(reg int i=n;i>=1;--i)
		for(reg int j=m;j>=1;--j){
			if(M[i][j+1])
				ri[i][j]=0;
			else
				ri[i][j]=ri[i][j+1]+1;
			if(M[i+1][j])
				dn[i][j]=0;
			else
				dn[i][j]=dn[i+1][j]+1;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			val[i][j]=min(min(le[i][j],ri[i][j]),min(up[i][j],dn[i][j]));
	reg int x=read()+1,y=read()+1;
	bfs(x,y);
	int ans1=inf,ans2=-inf;
	reg int p=read();
	for(reg int i=1;i<=p;++i){
		reg int x=read()+1,y=read()+1;
		if(ans1>dis[x][y]){
			ans1=dis[x][y];
			ans2=sum[x][y];
		}
		else if(ans1==dis[x][y]&&ans2<sum[x][y])
			ans2=sum[x][y];
	}
	printf("%d %d\n",ans1,ans2);

	fclose(stdin);
	fclose(stdout);
	return 0;
}