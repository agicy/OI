#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;
const int MAXK=1e6+5;
const int inf=0x3f3f3f3f;


int n,K,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int root,sum;
int siz[MAXN],MaxSon[MAXN];
bool del[MAXN];

inline void GetRoot(int u,int father){
	siz[u]=1,MaxSon[u]=0;
	for(int i=head[u];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			GetRoot(to[i],u);
			siz[u]+=siz[to[i]];
			MaxSon[u]=max(MaxSon[u],siz[to[i]]);
		}
	MaxSon[u]=max(MaxSon[u],sum-siz[u]);
	if(MaxSon[u]<MaxSon[root])
		root=u;
	return;
}

struct Node{
	int dep,dis;
	inline Node(void){
		dep=dis=0;
		return;
	}
	inline Node(int a,int b){
		dep=a,dis=b;
		return;
	}
};

int tot,dep[MAXN],dis[MAXN];
int vis[MAXK];
Node v[MAXN];

inline void DFS(int u,int father){
	v[++tot]=Node(dep[u],dis[u]);
	for(int i=head[u];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			dep[to[i]]=dep[u]+1,dis[to[i]]=dis[u]+w[i];
			DFS(to[i],u);
		}
	return;
}

int ans=inf;
Node Q[MAXN];

inline void Calc(int u){
	int p=0;
	vis[0]=0;
	for(int i=head[u];i;i=Next[i])
		if(!del[to[i]]){
			tot=0;
			dep[to[i]]=1,dis[to[i]]=w[i];
			DFS(to[i],0);
			for(int i=1;i<=tot;++i)
				if(v[i].dis<=K)
					ans=min(ans,vis[K-v[i].dis]+v[i].dep);
			for(int i=1;i<=tot;++i)
				if(v[i].dis<=K)
					vis[v[i].dis]=min(vis[v[i].dis],v[i].dep),Q[++p]=v[i];
		}
	for(int i=1;i<=p;++i)
		vis[Q[i].dis]=inf;
	return;
}

inline void Solve(int u){
	del[u]=true;
	Calc(u);
	for(int i=head[u];i;i=Next[i])
		if(!del[to[i]]){
			sum=siz[to[i]];
			MaxSon[root=0]=inf;
			GetRoot(to[i],0);
			Solve(root);
		}
	return;
}

int main(void){
	scanf("%d%d",&n,&K);
	for(int i=1;i<n;++i){
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		++a,++b;
		Add_Edge(a,b,c);
		Add_Edge(b,a,c);
	}
	memset(vis,0X3F,sizeof(vis));
	MaxSon[root=0]=sum=n;
	GetRoot(1,0);
	Solve(root);
	printf("%d\n",ans==inf?-1:ans);
	return 0;
}