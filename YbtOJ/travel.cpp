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

const int MAXN=500+5;
const int MAXM=1e3+5;
const int MAXE=2*MAXM;

int n,m;
int cnt,head[MAXN],to[MAXE],w[MAXE],Next[MAXE];
set<int> S[MAXN];

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

bool vis[MAXN];
int dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		static Node s;
		static set<int>::iterator it;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		reg int las=dis[u];
		it=lower_bound(S[u].begin(),S[u].end(),dis[u]);
		while(it!=S[u].end()&&las==*it){
			las=*it+1;
			++it;
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i],d=w[i]+las;
			if(dis[v]>d){
				dis[v]=d;
				Q.push(Node(v,d));
			}
		}
	}
	return;
}

int main(void){
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);

	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	for(reg int i=1;i<=n;++i){
		static int k;
		k=read();
		while(k--){
			static int x;
			x=read();
			S[i].insert(x);
		}
	}
	dijkstra(1);
	printf("%d\n",dis[n]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}