#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=1000+5;
const int MAXM=10000+5;
const int MAXP=100+5;
const int MAXD=100+5;
const int MAXC=100+5;

int n,m;
int p[MAXN];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		p[i]=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,d;
		u=read(),v=read(),d=read();
		Add_Edge(u,v,d);
		Add_Edge(v,u,d);
	}
	return;
}

struct Node{
	int ID,v,dis;
	inline Node(void){
		ID=v=dis=0;
		return;
	}
	inline Node(reg int a,reg int b,reg int c){
		ID=a,v=b,dis=c;
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXN][MAXC];
int dis[MAXN][MAXC];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline int Dijkstra(const Node& s,reg int e,reg int c){
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())
		Q.pop();
	dis[s.ID][s.v]=s.dis;
	Q.push(s);
	while(!Q.empty()){
		static Node temp;
		temp=Q.top();
		Q.pop();
		reg int ID=temp.ID,v=temp.v;
		vis[ID][v]=true;
		if(ID==e)
			return temp.dis;
		if(v<c&&!vis[ID][v+1]&&dis[ID][v+1]>dis[ID][v]+p[ID]){
			dis[ID][v+1]=dis[ID][v]+p[ID];
			Q.push(Node(ID,v+1,dis[ID][v+1]));
		}
		for(reg int i=head[ID];i;i=Next[i])
			if(w[i]<=v&&!vis[to[i]][v-w[i]]&&dis[to[i]][v-w[i]]>dis[ID][v]){
				dis[to[i]][v-w[i]]=dis[ID][v];
				Q.push(Node(to[i],v-w[i],dis[to[i]][v-w[i]]));
			}
	}
	return INF;
}

inline void Work(void){
	int Q=read();
	while(Q--){
		static int c,s,e;
		c=read(),s=read(),e=read();
		reg int ans=Dijkstra(Node(s,0,0),e,c);
		if(ans==INF)
			puts("impossible");
		else
			printf("%d\n",ans);
	}
	return;
}
