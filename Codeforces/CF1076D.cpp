#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=3e5+5;
const int MAXM=3e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Edge{
	int v,w,id;
	inline Edge(reg int v=0,reg int w=0,reg int id=0):v(v),w(w),id(id){
		return;
	}
};

int n,m,k;
vector<Edge> G[MAXN];

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

bool vis[MAXN];
int fr[MAXN];
ll dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
vector<int> ans;

inline void dijkstra(reg int s){
	fill(dis+1,dis+n+1,inf);
	dis[s]=0,Q.push(Node(s,dis[s]));
	while(!Q.empty()&&ans.size()<k){
		static Node p;
		p=Q.top();
		Q.pop();
		reg int u=p.id;
		if(vis[u])
			continue;
		vis[u]=true;
		if(u!=s)
			ans.push_back(fr[u]);
		for(Edge e:G[u])
			if(dis[e.v]>dis[u]+e.w){
				fr[e.v]=e.id;
				dis[e.v]=dis[u]+e.w;
				Q.push(Node(e.v,dis[e.v]));
			}
	}
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		G[u].push_back(Edge(v,w,i)),G[v].push_back(Edge(u,w,i));
	}
	dijkstra(1);
	write(ans.size()),putchar('\n');
	for(reg int i=0,siz=ans.size();i<siz;++i)
		write(ans[i]),putchar(i==siz-1?'\n':' ');
	flush();
	return 0;
}