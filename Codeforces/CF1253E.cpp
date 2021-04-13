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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=80;
const int MAXM=1e5+5;
const int MAXV=MAXM*2;
const int MAXE=MAXM*MAXN;

int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
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

bool vis[MAXV];
int dis[MAXV];
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
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

int n,m;
int a[MAXN],b[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		a[i]=read(),b[i]=read();
	for(reg int i=1;i<=m;++i)
		Add_Edge(i,i+1,1),Add_Edge(i+1,i,0);
	for(reg int i=0;i<n;++i){
		reg int k=0,l=max(1,a[i]-b[i]),r=min(a[i]+b[i]+1,m+1);
		while(true){
			l=max(1,l),r=min(r,m+1);
			Add_Edge(l,r,k);
			++k;
			if(l==1||r==m+1)
				break;
			--l,++r;
		}
	}
	reg int s=1,t=m+1;
	dijkstra(s);
	printf("%d\n",dis[t]);
	return 0;
}