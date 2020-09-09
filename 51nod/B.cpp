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

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXK=MAXN;

int n,m,k;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
ll dis[MAXN];
int key[MAXK];

struct Node{
	int id;
	ll dis;
	inline Node(reg int id=0,reg ll dis=0):id(id),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,c;
		x=read(),y=read(),c=read();
		Add_Edge(x,y,c);
		Add_Edge(y,x,c);
	}
	for(reg int i=1;i<=k;++i)
		key[i]=read();
	ll ans=0x3f3f3f3f3f3f3f3fll;
	for(reg int i=1;(1<<i)<=k;++i){
		memset(vis,false,sizeof(vis));
		memset(dis,0x3f,sizeof(dis));
		while(!Q.empty())Q.pop();
		for(reg int j=1;j<=k;++j)
			if((j>>i)&1){
				reg int u=key[j];
				dis[u]=0,Q.push(Node(u,0));
			}
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
					dis[v]=dis[u]+w[i];
					Q.push(Node(v,dis[v]));
				}
			}
		}
		for(reg int j=1;j<=k;++j)
			if(!((j>>i)&1)){
				reg int u=key[j];
				ans=min(ans,dis[u]);
			}
	}
	printf("%lld\n",ans);
	return 0;
}