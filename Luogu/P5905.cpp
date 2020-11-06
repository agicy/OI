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

const int MAXN=3e3+5;
const int MAXM=6e3+5;

int n,m;
int u[MAXM],v[MAXM],w[MAXM];

namespace Graph{
	const int MAXV=MAXN;
	const int MAXE=MAXM+MAXN;
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	bool inque[MAXV];
	int in[MAXV];
	int dis[MAXV];
	queue<int> Q;
	inline bool spfa(reg int s){
		memset(dis,0x3f,sizeof(dis));
		inque[s]=true,dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>dis[u]+w[i]){
					dis[v]=dis[u]+w[i];
					if(!inque[v]){
						inque[v]=true;
						++in[v];
						if(in[v]>n+1)
							return false;
						Q.push(v);
					}
				}
			}
		}
		return true;
	}
}

namespace VG{
	const int MAXV=MAXN;
	const int MAXE=MAXM;
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int id,val;
		inline Node(reg int id=0,reg int val=0):id(id),val(val){
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
	int dis[MAXV];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void dijkstra(reg int s){
		memset(vis,false,sizeof(vis));
		memset(dis,0x3f,sizeof(dis));
		while(!Q.empty())Q.pop();
		dis[s]=0,Q.push(Node(s,0));
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
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read(),w[i]=read();
		Graph::Add_Edge(u[i],v[i],w[i]);
	}
	for(reg int i=1;i<=n;++i)
		Graph::Add_Edge(0,i,0);
	reg bool f=Graph::spfa(0);
	if(!f)
		puts("-1");
	else{
		for(reg int i=1;i<=m;++i)
			VG::Add_Edge(u[i],v[i],Graph::dis[u[i]]+w[i]-Graph::dis[v[i]]);
		for(reg int i=1;i<=n;++i){
			VG::dijkstra(i);
			reg ll sum=0;
			for(reg int j=1;j<=n;++j)
				if(VG::dis[j]>1e9)
					sum+=1e9*j;
				else
					sum+=1ll*j*(VG::dis[j]+Graph::dis[j]-Graph::dis[i]);
			printf("%lld\n",sum);
		}
	}
	return 0;
}