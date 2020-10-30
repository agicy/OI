#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXK=1e4+5;
const int inf=0x3f3f3f3f;

struct Edge{
	int v,w;
	inline Edge(int v=0,int w=0):v(v),w(w){
		return;
	}
};

int n,m,k,r,q;
vector<Edge> G[MAXN+MAXK];

inline void Add_Edge(int u,int v,int len){
	G[u].push_back(Edge(v,len));
	return;
}

inline int ceil(int a,int b){
	if(a%b)
		return a/b+1;
	else
		return a/b;
}

struct Node{
	int id,dis,cos;
	inline Node(int id=0,int dis=0,int cos=0):id(id),dis(dis),cos(cos){
		return;
	}
	inline int getVal(void)const{
		return ceil(dis,r)+cos;
	}
	inline bool operator<(const Node& a)const{
		int val1=getVal(),val2=a.getVal();
		if(val1!=val2)
			return val1<val2;
		else
			return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		int val1=getVal(),val2=a.getVal();
		if(val1!=val2)
			return val1>val2;
		else
			return dis>a.dis;
	}
};

bool vis[MAXN];
Node dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline int dijkstra(int s,int t){
	fill(vis+1,vis+n+k+1,false);
	fill(dis+1,dis+n+k+1,Node(0,inf,inf));
	while(!Q.empty())Q.pop();
	dis[s]=Node(s,0,0),Q.push(Node(s,0,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		int u=s.id,v,w;
		if(vis[u])
			continue;
		vis[u]=true;
		if(u==t)
			return dis[t].getVal();
		for(auto E:G[u]){
			v=E.v,w=E.w;
			if(v>n){
				s=Node(v,0,dis[u].getVal()+w);
				if(dis[v]>s){
					dis[v]=s;
					Q.push(s);
				}
			}
			else{
				s=Node(v,dis[u].dis+w,dis[u].cos);
				if(dis[v]>s){
					dis[v]=s;
					Q.push(s);
				}
			}
		}
	}
	return inf;
}

int main(void){
	n=read(),m=read(),k=read(),r=read(),q=read();
	for(int i=1;i<=m;++i){
		static int u,v,d;
		u=read(),v=read(),d=read();
		Add_Edge(u,v,d);
		Add_Edge(v,u,d);
	}
	for(int i=1;i<=k;++i){
		static int t,c;
		t=read(),c=read();
		for(int j=0;j<t;++j){
			static int x;
			x=read();
			Add_Edge(x,i+n,c);
			Add_Edge(i+n,x,0);
		}
	}
	while(q--){
		static int a,b;
		a=read(),b=read();
		int ans=dijkstra(a,b);
		printf("%d\n",ans);
	}
	return 0;
}