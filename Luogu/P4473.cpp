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

const int MAXN=150+5;
const int MAXM=150+5;
const int inf=0X3F3F3F3F;

struct Point{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
};

struct Node{
	int x,y,dis;
	inline Node(reg int x=0,reg int y=0,reg int dis=0):x(x),y(y),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

int n,m;
int b[MAXN][MAXM],a[MAXN][MAXM];
Point s[3];
int dis[3][MAXN][MAXM];
bool vis[MAXN][MAXM];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
int fa[MAXN][MAXM];

inline int find(reg int fa[],reg int x){
	return fa[x]?fa[x]=find(fa,fa[x]):x;
}

inline void Dijkstra(Point s,reg int dis[MAXN][MAXM]){
	memset(vis,false,sizeof(vis));
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			dis[i][j]=inf;
	memset(fa,0,sizeof(fa));
	while(!Q.empty())Q.pop();
	dis[s.x][s.y]=0,fa[s.x][s.y]=s.y+1,Q.push(Node(s.x,s.y,a[s.x][s.y]));
	while(!Q.empty()){
		static Node u;
		u=Q.top();
		Q.pop();
		reg int x=u.x,y=u.y;
		if(vis[x][y])
			continue;
		vis[x][y]=true;
		reg int lx=max(1,x-b[x][y]),rx=min(n,x+b[x][y]);
		for(reg int i=lx;i<=rx;++i){
			reg int len=b[x][y]-abs(i-x);
			reg int up=max(1,y-len),dw=min(m,y+len);
			for(reg int j=find(fa[i],up);j<=dw;j=find(fa[i],j)){
				if(dis[i][j]>dis[x][y]+a[x][y]){
					dis[i][j]=dis[x][y]+a[x][y];
					Q.push(Node(i,j,dis[i][j]+a[i][j]));
				}
				fa[i][j]=j+1;
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			b[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read();
	for(reg int i=0;i<3;++i)
		s[i].Read();
	for(reg int i=0;i<3;++i)
		Dijkstra(s[i],dis[i]);
	reg int pos=-1,Min=inf;
	for(reg int i=0;i<3;++i){
		reg int sum=0;
		for(reg int j=0;j<3;++j)
			sum+=dis[j][s[i].x][s[i].y];
		if(Min>sum){
			pos=i;
			Min=sum;
		}
	}
	if(pos==-1)
		puts("NO");
	else
		printf("%c\n%d\n",'X'+pos,Min);
	return 0;
}