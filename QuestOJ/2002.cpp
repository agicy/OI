#include<cstdio>
#include<cstring>
#include<vector>
using std::vector;
#include<queue>
using std::priority_queue;
using std::greater;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3Fll
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

struct Node{
	int ID,cnt;
	ll dis;
	inline Node(void){
		ID=cnt=dis=0;
		return;
	}
	inline Node(reg int a,reg int b,reg ll c){
		ID=a,cnt=b,dis=c;
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

const int MAXN=1000+5;
const int MAXM1=3000+5;
const int MAXM2=300+5;

bool vis[MAXN][MAXM2];
int n,m1,m2;
int cnt,head[MAXN],to[MAXM1+MAXM2],Next[MAXM1+MAXM2];
ll w[MAXM1+MAXM2];
ll dis[MAXN][MAXM2];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Read(void);
inline void Work(void);
inline void Add_Edge(reg int,reg int,reg ll);
inline void Dijkstra(int,int);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m1=read(),m2=read();
	for(reg int i=1;i<=m1;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
	}
	for(reg int i=1;i<=m2;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v,0);
	}
	return;
}

inline void Work(void){
	Dijkstra(1,0);
	ll ans=INF,pos=-1;
	for(reg int i=0;i<=m2;++i)
		if(ans>dis[n][i]){
			ans=dis[n][i];
			pos=i;
		}
	if(ans==INF)
		puts("-1");
	else
		printf("%lld\n%lld\n",pos,ans);
	return;
}

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Dijkstra(int s,int s_cnt){
	reg int i,ID,cnt;
	static Node temp;
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())
		Q.pop();
	dis[s][s_cnt]=0,Q.push(Node(s,s_cnt,0));
	while(!Q.empty()){
		temp=Q.top();
		Q.pop();
		ID=temp.ID;
		cnt=temp.cnt;
		if(vis[ID][cnt])
			continue;
		vis[ID][cnt]=true;
		for(i=head[ID];i;i=Next[i]){
			if(w[i]){
				if(dis[to[i]][cnt]>dis[ID][cnt]+w[i]){
					dis[to[i]][cnt]=dis[ID][cnt]+w[i];
					Q.push(Node(to[i],cnt,dis[to[i]][cnt]));
				}
			}
			else if(cnt<m2){
				if(dis[to[i]][cnt+1]>dis[ID][cnt]){
					dis[to[i]][cnt+1]=dis[ID][cnt];
					Q.push(Node(to[i],cnt+1,dis[to[i]][cnt+1]));
				}
			}
		}
	}
	return;
}
