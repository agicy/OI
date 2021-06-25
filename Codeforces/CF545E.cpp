#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=3e5+5;
const int MAXM=3e5+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
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

bool vis[MAXN];
ll dis[MAXN];
int from[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,dis[s]));
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
				from[v]=i;
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
			else if(dis[v]==dis[u]+w[i]&&w[from[v]]>w[i])
				from[v]=i;
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	dijkstra(read());
	reg ll sum=0;
	reg int tot=0;
	static int ans[MAXN];
	for(reg int i=1;i<=n;++i)
		sum+=w[from[i]];
	for(reg int i=1;i<=n;++i)
		ans[++tot]=(from[i]+1)>>1;
	sort(ans+1,ans+tot+1);
	write(sum),putchar('\n');
	for(reg int i=2;i<=tot;++i)
		write(ans[i]),putchar(i==tot?'\n':' ');
	flush();
	return 0;
}