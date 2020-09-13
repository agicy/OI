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

const int MAXN=1e3+5;
const int MAXM=MAXN*(MAXN-1)/2;
const ll p=2147483647ll;

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

int T[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,l;
		x=read(),y=read(),l=read();
		Add_Edge(x,y,l);
		Add_Edge(y,x,l);
	}
	dijkstra(1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=head[i];j;j=Next[j]){
			reg int v=to[j];
			if(dis[v]==dis[i]+w[j])
				++T[v];
		}
	reg ll ans=1;
	for(reg int i=1;i<=n;++i)
		if(T[i])
			ans=ans*T[i]%p;
	printf("%lld\n", ans);
	return 0;
}