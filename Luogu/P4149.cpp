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

const int MAXN=200000+5;
const int MAXK=1000000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int K;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),K=read();
	for(reg int i=1;i<n;++i){
		static int a,b,c;
		a=read()+1,b=read()+1,c=read();
		Add_Edge(a,b,c);
		Add_Edge(b,a,c);
	}
	return;
}

int root,sum;
int size[MAXN],MaxSon[MAXN];
bool del[MAXN];

inline void GetRoot(reg int ID,reg int father){
	size[ID]=1,MaxSon[ID]=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			GetRoot(to[i],ID);
			size[ID]+=size[to[i]];
			MaxSon[ID]=max(MaxSon[ID],size[to[i]]);
		}
	MaxSon[ID]=max(MaxSon[ID],sum-size[ID]);
	if(MaxSon[ID]<MaxSon[root])
		root=ID;
	return;
}

struct Node{
	int dep,dis;
	inline Node(void){
		dep=dis=0;
		return;
	}
	inline Node(reg int a,reg int b){
		dep=a,dis=b;
		return;
	}
};

int tot,dep[MAXN],dis[MAXN];
int vis[MAXK];
Node v[MAXN];

inline void DFS(reg int ID,reg int father){
	v[++tot]=Node(dep[ID],dis[ID]);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			dep[to[i]]=dep[ID]+1,dis[to[i]]=dis[ID]+w[i];
			DFS(to[i],ID);
		}
	return;
}

int ans=INF;
Node Q[MAXN];

inline void Calc(reg int ID){
	reg int p=0;
	vis[0]=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(!del[to[i]]){
			tot=0;
			dep[to[i]]=1,dis[to[i]]=w[i];
			DFS(to[i],0);
			for(reg int i=1;i<=tot;++i)
				if(v[i].dis<=K)
					ans=min(ans,vis[K-v[i].dis]+v[i].dep);
			for(reg int i=1;i<=tot;++i)
				if(v[i].dis<=K)
					vis[v[i].dis]=min(vis[v[i].dis],v[i].dep),Q[++p]=v[i];
		}
	for(reg int i=1;i<=p;++i)
		vis[Q[i].dis]=INF;
	return;
}

inline void Solve(reg int ID){
	del[ID]=true;
	Calc(ID);
	for(reg int i=head[ID];i;i=Next[i])
		if(!del[to[i]]){
			sum=size[to[i]];
			MaxSon[root=0]=INF;
			GetRoot(to[i],0);
			Solve(root);
		}
	return;
}

inline void Work(void){
	memset(vis,0X3F,sizeof(vis));
	MaxSon[root=0]=sum=n;
	GetRoot(1,0);
	Solve(root);
	printf("%d\n",ans==INF?-1:ans);
	return;
}
