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

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int MAXN=1e3+5;
const int MAXM=2e3+5;
const int MAXW=500+5;
const int inf=0x3f3f3f3f;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id,dep,val;
	inline Node(reg int id=0,reg int dep=0,reg int val=0):id(id),dep(dep),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

bool vis[MAXN][MAXW];
int dis[MAXN][MAXW];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int sid,reg int Maxw){
	for(reg int i=1;i<=Maxw;++i)
		dis[sid][i]=0,Q.push(Node(sid,i,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id,dep=s.dep;
		if(vis[u][dep])
			continue;
		vis[u][dep]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i],W=w[i];
			if(W%dep)
				continue;
			reg int w=W/dep;
			for(reg int vdep=dep;vdep<=Maxw;vdep+=dep)
				if(dis[v][vdep]>dis[u][dep]+w){
					dis[v][vdep]=dis[u][dep]+w;
					Q.push(Node(v,vdep,dis[v][vdep]));
				}
		}
	}
	return;
}

int main(void){
	//freopen("magic.in","r",stdin);
	//freopen("magic.out","w",stdout);

	n=read(),m=read();
	int Maxw=0;
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
		Maxw=max(Maxw,w);
	}
	memset(dis,0x3f,sizeof(dis));
	dijkstra(n,Maxw);
	reg int Q=read();
	while(Q--){
		static int p;
		p=read();
		int ans=inf;
		for(reg int i=1;i<=Maxw;++i)
			ans=min(ans,dis[p][i]);
		printf("%d\n",ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}