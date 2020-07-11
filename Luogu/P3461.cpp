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

const int MAXN=5000+5;
const int MAXM=500000+5;
const int MAXP=5000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

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

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read(),u[i]=read();
		Add_Edge(a[i],b[i],u[i]);
		Add_Edge(b[i],a[i],u[i]);
	}
	p=read();
	for(reg int i=1;i<=p;++i)
		key[i]=read();
	return;
}

struct Node{
	int ID,val;
	inline Node(reg int ID=0,reg int val=0):ID(ID),val(val){
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

inline void Dijkstra(reg int s){
	//memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	dis[s]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		reg int ID=Q.top().ID;
		Q.pop();
		if(vis[ID])
			continue;
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+w[i]){
				pre[to[i]]=ID;
				dis[to[i]]=dis[ID]+w[i];
				Q.push(Node(to[i],dis[to[i]]));
			}
	}
	return;
}

struct UnionFind{
	int fa[MAXN],rank[MAXN];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			fa[i]=i,rank[i]=1;
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
		if(rank[ra]>rank[rb])
			fa[rb]=ra;
		else if(rank[ra]==rank[rb]){
			fa[rb]=ra;
			++rank[ra];
		}
		else
			fa[ra]=rb;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

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
UnionFind U;
vector<Edge> V,Ans;

inline void Work(void){
	Dijkstra(key[1]);
	T[key[1]]=true;
	for(reg int i=1;i<=p;++i)
		for(reg int j=key[i];!T[j];j=pre[j])
			T[j]=true;
	for(reg int i=1;i<=m;++i)
		if(T[a[i]]&&T[b[i]])
			V.push_back(Edge(a[i],b[i],u[i]));
	sort(V.begin(),V.end());
	U.Init(n);
	reg int ans=0;
	for(reg int i=0,size=V.size();i<size;++i)
		if(!U.search(V[i].f,V[i].t)){
			ans+=V[i].val;
			U.merge(V[i].f,V[i].t);
			Ans.push_back(V[i]);
		}
	printf("%d %llu\n",ans,Ans.size());
	for(reg int i=0,size=Ans.size();i<size;++i)
		printf("%d %d\n",Ans[i].f,Ans[i].t);
	return;
}
