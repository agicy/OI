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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXS=50+5;
const int MAXN=50+5;
const int MAXM=50+5;
const int inf=0x3f3f3f3f;

struct Box{
	int n,m;
	int ch[MAXN][2];
	bool tag[MAXM];
};

int S;
Box a[MAXS];
int dis[MAXS][MAXS];

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

bool vis[MAXN][MAXN];
queue<Node> Q;

inline bool bfs(const Box& a,const Box& b){
	memset(vis,false,sizeof(vis));
	while(!Q.empty())Q.pop();
	vis[0][0]=true,Q.push(Node(0,0));
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg int x=s.x,y=s.y;
		if(a.tag[x]&&!b.tag[y])
			return false;
		for(reg int i=0;i<2;++i){
			reg int fx=a.ch[x][i],fy=b.ch[y][i];
			if(!vis[fx][fy]){
				vis[fx][fy]=true;
				Q.push(Node(fx,fy));
			}
		}
	}
	return true;
}

int main(void){
	S=read();
	for(reg int i=1;i<=S;++i){
		a[i].n=read(),a[i].m=read();
		for(reg int j=1;j<=a[i].m;++j)
			a[i].tag[read()]=true;
		for(reg int j=0;j<a[i].n;++j)
			a[i].ch[j][0]=read(),a[i].ch[j][1]=read();
	}
	for(reg int i=1;i<=S;++i)
		for(reg int j=1;j<=S;++j)
			dis[i][j]=-inf;
	for(reg int i=1;i<=S;++i)
		for(reg int j=1;j<=S;++j)
			if(i!=j&&bfs(a[i],a[j])&&dis[j][i]<0)
				dis[i][j]=1;
	reg int ans=-1;
	for(reg int k=1;k<=S;++k)
		for(reg int i=1;i<=S;++i)
			for(reg int j=1;j<=S;++j)
				if(dis[i][j]<dis[i][k]+dis[k][j]&&dis[i][k]>0&&dis[k][j]>0){
					dis[i][j]=dis[i][k]+dis[k][j];
					ans=max(ans,dis[i][j]);
				}
	printf("%d\n",ans+1);
	return 0;
}