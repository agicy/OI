#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int MAXM=100+5;

int n,m,K;
int c[MAXM];
int tot,can[MAXN];
int r[MAXN],d[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,len);
	return;
}

int ans;

struct Node{
	int ID,dis;
	inline Node(reg int ID=0,reg int dis=0):ID(ID),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXN];
int dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline int Dijkstra(void){
	memset(vis,false,sizeof(vis));
	memset(dis,10,sizeof(dis));
	while(!Q.empty())Q.pop();
	for(reg int i=1;i<=m;++i)
		dis[c[i]]=0,Q.push(Node(c[i],dis[c[i]]));
	for(reg int i=1;i<=K;++i)
		dis[can[i]]=0,Q.push(Node(can[i],dis[can[i]]));
	while(!Q.empty()){
		reg int ID=Q.top().ID;
		Q.pop();
		if(vis[ID])
			continue;
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+w[i]){
				dis[to[i]]=dis[ID]+w[i];
				Q.push(Node(to[i],dis[to[i]]));
			}
	}
	int Max=0;
	for(reg int i=1;i<=n;++i)
		Max=max(Max,dis[i]);
	return Max;
}

const double delta=0.99;

inline void SA(void){
	for(reg double T=2000;T>1e-14;T*=delta){
		reg int x=rand()%K+1,y=rand()%(tot-K)+1;
		swap(can[x],can[K+y]);
		reg int tmp=Dijkstra(),Del=tmp-ans;
		if(Del<0)
			ans=tmp;
		else if(exp(-Del/T)*RAND_MAX<=rand())
			swap(can[x],can[K+y]);
	}
	return;
}

bool V[MAXN];

int main(void){
	srand(time(0));
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=n;++i)
		r[i]=read()+1;
	for(reg int i=1;i<=n;++i)
		d[i]=read();
	for(reg int i=1;i<=n;++i)
		Add_Tube(i,r[i],d[i]);
	ans=Dijkstra();
	for(reg int i=1;i<=m;++i){
		c[i]=read()+1;
		V[c[i]]=true;
	}
	for(reg int i=1;i<=n;++i)
		if(!V[i])
			can[++tot]=i;
	if(m+K==n)
		printf("%d\n",Dijkstra());
	else{
		while(clock()<=0.6*CLOCKS_PER_SEC)
			SA();
		printf("%d\n",ans);
	}
	return 0;
}