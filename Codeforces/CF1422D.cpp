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

const int MAXM=1e5+5;
const int MAXV=MAXM;
const int MAXE=6*MAXM;

struct Point{
	int id,x,y;
	inline void Read(reg int i){
		id=i,x=read(),y=read();
		return;
	}
};

int n,m;
int sx,sy,fx,fy;
Point a[MAXM];
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id;
	ll val;
	inline Node(reg int id=0,reg ll val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

bool vis[MAXV];
ll dis[MAXV];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,dis[s]));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read(),sx=read(),sy=read(),fx=read(),fy=read();
	for(reg int i=1;i<=m;++i)
		a[i].Read(i);
	Add_Edge(0,m+1,abs(sx-fx)+abs(sy-fy));
	for(reg int i=1;i<=m;++i){
		Add_Edge(0,i,min(abs(sx-a[i].x),abs(sy-a[i].y)));
		Add_Edge(i,m+1,abs(fx-a[i].x)+abs(fy-a[i].y));
	}
	sort(a+1,a+m+1,[](const Point& a,const Point& b){return a.x<b.x;});
	for(reg int i=1;i<m;++i){
		reg int dx=a[i+1].x-a[i].x;
		Add_Edge(a[i].id,a[i+1].id,dx);
		Add_Edge(a[i+1].id,a[i].id,dx);
	}
	sort(a+1,a+m+1,[](const Point& a,const Point& b){return a.y<b.y;});
	for(reg int i=1;i<m;++i){
		reg int dy=a[i+1].y-a[i].y;
		Add_Edge(a[i].id,a[i+1].id,dy);
		Add_Edge(a[i+1].id,a[i].id,dy);
	}
	dijkstra(0);
	printf("%lld\n",dis[m+1]);
	return 0;
}