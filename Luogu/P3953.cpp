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

const int MAXN=100000+5;
const int MAXM=200000+5;
const int MAXK=50+5;

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Init();
		Read();
		Work();
	}
	return 0;
}

struct Graph{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Init(void){
		cnt=0;
		memset(head,0,sizeof(head));
		return;
	}
	inline void Add_Edge(const int& u,const int& v,const int& len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
};

int n,m,K,P;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
Graph G,Gp;

inline void Read(void){
	n=read(),m=read(),K=read(),P=read();
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		G.Add_Edge(a,b,c);
		Gp.Add_Edge(b,a,c);
	}
	return;
}

struct Node{
	int ID,dis;
	inline Node(const int& ID=0,const int& dis=0):ID(ID),dis(dis){
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

inline void Dijkstra(const int& s,const Graph& G){
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	dis[s]=0,Q.push(Node(s,dis[s]));
	while(!Q.empty()){
		reg int ID=Q.top().ID;
		Q.pop();
		if(vis[ID])
			continue;
		vis[ID]=true;
		for(reg int i=G.head[ID];i;i=G.Next[i])
			if(dis[G.to[i]]>dis[ID]+G.w[i]){
				dis[G.to[i]]=dis[ID]+G.w[i];
				Q.push(Node(G.to[i],dis[G.to[i]]));
			}
	}
	return;
}

bool flag;
bool inStack[MAXN][MAXK];
int f[MAXN][MAXK];

inline int DFS(const int& ID,const int& k,const Graph& G){
	if(inStack[ID][k]){
		flag=true;
		return 0;
	}
	if(f[ID][k]>0)
		return f[ID][k];
	inStack[ID][k]=true;
	reg int sum=0;
	for(reg int i=G.head[ID];i;i=G.Next[i]){
		int temp=k-(dis[G.to[i]]-dis[ID]+G.w[i]);
		if(0<=temp&&temp<=K)
			sum=(sum+DFS(G.to[i],temp,G))%P;
		if(flag){
			inStack[ID][k]=false;
			return 0;
		}
	}
	if(ID==n&&k==0)
		sum=1;
	inStack[ID][k]=false;
	return f[ID][k]=sum;
}

inline void Work(void){
	Dijkstra(n,Gp);
	reg int ans=0;
	for(int i=0;i<=K;++i)
		ans=(ans+DFS(1,i,G))%P;
	if(flag)
		puts("-1");
	else
		printf("%d\n",ans);
	return;
}

inline void Init(void){
	flag=false;
	G.Init();
	Gp.Init();
	memset(f,0,sizeof(f));
	return;
}
