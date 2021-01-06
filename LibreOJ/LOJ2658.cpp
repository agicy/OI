#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e3+5;
const int MAXM=5e5+5;
const int MAXP=5e3+5;

int n,m,p;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
int a[MAXM],b[MAXM],u[MAXM];
int key[MAXP];

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
int pre[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		reg int u=Q.top().id;
		Q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i])
			if(dis[to[i]]>dis[u]+w[i]){
				pre[to[i]]=u;
				dis[to[i]]=dis[u]+w[i];
				Q.push(Node(to[i],dis[to[i]]));
			}
	}
	return;
}

namespace UnionFind{
	int fa[MAXN],rnk[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,rnk[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra==rb)
			return;
		if(rnk[ra]>rnk[rb])
			fa[rb]=ra;
		else if(rnk[ra]==rnk[rb]){
			fa[rb]=ra;
			++rnk[ra];
		}
		else
			fa[ra]=rb;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

struct Edge{
	int f,t,val;
	inline Edge(reg int f=0,reg int t=0,reg int val=0):f(f),t(t),val(val){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return val<a.val;
	}
};

bool T[MAXN];
vector<Edge> V,Ans;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read(),u[i]=read();
		Add_Edge(a[i],b[i],u[i]);
		Add_Edge(b[i],a[i],u[i]);
	}
	p=read();
	for(reg int i=1;i<=p;++i)
		key[i]=read();
	dijkstra(key[1]);
	T[key[1]]=true;
	for(reg int i=1;i<=p;++i)
		for(reg int j=key[i];!T[j];j=pre[j])
			T[j]=true;
	for(reg int i=1;i<=m;++i)
		if(T[a[i]]&&T[b[i]])
			V.push_back(Edge(a[i],b[i],u[i]));
	sort(V.begin(),V.end());
	UnionFind::Init(n);
	reg int ans=0;
	for(Edge e:V)
		if(!UnionFind::search(e.f,e.t)){
			ans+=e.val;
			UnionFind::merge(e.f,e.t);
			Ans.push_back(e);
		}
	printf("%d %lu\n",ans,Ans.size());
	for(Edge e:Ans)
		printf("%d %d\n",e.f,e.t);
	return 0;
}