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

const int MAXN=1e3+5;
const int MAXP=1e4+5;
const int MAXK=1e3+5;
const int inf=0x3f3f3f3f;

int n,p,k;
int cnt,head[MAXN],to[MAXP<<1],w[MAXP<<1],Next[MAXP<<1];

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

bool vis[MAXK][MAXN];
int dis[MAXK][MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int sid,reg int sdep){
	memset(dis,0x3f,sizeof(dis));
	dis[sdep][sid]=0,Q.push(Node(sid,sdep,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id,dep=s.dep;
		if(vis[dep][u])
			continue;
		vis[dep][u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep<k&&dis[dep+1][v]>dis[dep][u]){
				dis[dep+1][v]=dis[dep][u];
				Q.push(Node(v,dep+1,dis[dep+1][v]));
			}
			if(dis[dep][v]>max(dis[dep][u],w[i])){
				dis[dep][v]=max(dis[dep][u],w[i]);
				Q.push(Node(v,dep,dis[dep][v]));
			}
		}
	}
	return;
}

int main(void){
	n=read(),p=read(),k=read();
	for(reg int i=1;i<=p;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		Add_Edge(a,b,l);
		Add_Edge(b,a,l);
	}
	dijkstra(1,0);
	int ans=inf;
	for(reg int i=0;i<=k;++i)
		ans=min(ans,dis[k][n]);
	printf("%d\n",ans==inf?-1:ans);
	return 0;
}