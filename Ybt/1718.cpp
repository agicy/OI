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

const int MAXN=5e4+5;
const int MAXM=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

struct Edge{
	int x,y;
	ll l;
	inline Edge(reg int x=0,reg int y=0,reg ll l=0):x(x),y(y),l(l){
		return;
	}
};

struct Graph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	ll w[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg ll len){
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
	inline void dijkstra(reg int s,reg ll dis[]){
		static bool vis[MAXN];
		static priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
		memset(vis,false,sizeof(vis));
		while(!Q.empty())Q.pop();
		dis[s]=0,Q.push(Node(s,0));
		while(!Q.empty()){
			reg int u=Q.top().id;
			Q.pop();
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
};

int n,m;
Edge E[MAXM];
ll disa[MAXN],disb[MAXN],disc[MAXN],disd[MAXN];
Graph G1,G2,G3;
int f[MAXN],inDeg[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		static ll l;
		x=read(),y=read(),l=read();
		E[i]=Edge(x,y,l);
		G1.Add_Edge(x,y,l);
		G2.Add_Edge(y,x,l);
	}
	int a,b,c,d;
	a=read(),b=read(),c=read(),d=read();
	memset(disa,0x3f,sizeof(disa)),memset(disb,0x3f,sizeof(disb)),memset(disc,0x3f,sizeof(disc)),memset(disd,0x3f,sizeof(disd));
	G1.dijkstra(a,disa),G1.dijkstra(c,disc),G2.dijkstra(b,disb),G2.dijkstra(d,disd);
	if(disa[b]>=inf||disc[d]>=inf)
		puts("-1");
	else{
		int ans=0;
		for(reg int i=1;i<=n;++i)
			if(disa[i]+disb[i]==disa[b]&&disc[i]+disd[i]==disc[d])
				ans=f[i]=1;
		if(!ans)
			puts("0");
		else{
			for(reg int i=1;i<=m;++i){
				reg int u=E[i].x,v=E[i].y,w=E[i].l;
				if(disa[u]+w+disb[v]==disa[b]&&disc[u]+w+disd[v]==disc[d]){
					++inDeg[v];
					G3.Add_Edge(u,v);
				}
			}
			queue<int> Q;
			for(int i=1;i<=n;++i)
				if(!inDeg[i])
					Q.push(i);
			while(!Q.empty()){
				reg int u=Q.front();
				Q.pop();
				ans=max(ans,f[u]);
				for(reg int i=G3.head[u];i;i=G3.Next[i]){
					int v=G3.to[i];
					--inDeg[v];
					f[v]=max(f[v],f[u]+1);
					if(!inDeg[v])
						Q.push(v);
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}