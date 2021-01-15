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

const int MAXN=1000000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

int size[MAXN];
int root,MaxRootPart;

inline void GetRoot(reg int ID,reg int father){
	int MaxPart=0;
	size[ID]=1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			GetRoot(to[i],ID);
			size[ID]+=size[to[i]];
			MaxPart=max(MaxPart,size[to[i]]);
		}
	MaxPart=max(MaxPart,n-size[ID]);
	if(MaxPart<MaxRootPart){
		root=ID;
		MaxRootPart=MaxPart;
	}
	return;
}

inline void DFS(reg int ID,reg int father){
	size[ID]=1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			size[ID]+=size[to[i]];
		}
	return;
}

bool vis[MAXN];
int tot;
int ans[MAXN];

inline void GetAns(reg int ID,reg int father,reg int sum){
	vis[ID]=true;
	ans[ID]=tot;
	if(size[ID]+sum>=(n+1)/2)
		--ans[ID];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			GetAns(to[i],ID,sum);
	return;
}

inline bool cmp(reg int a,reg int b){
	return size[a]>size[b];
}

vector<int> V;

inline void Work(void){
	size[root=0]=MaxRootPart=INF;
	GetRoot(1,0);
	DFS(root,0);
	V.push_back(0);
	for(reg int i=head[root];i;i=Next[i])
		V.push_back(to[i]);
	sort(V.begin(),V.end(),cmp);
	reg int sum=0;
	for(reg int i=1;i<(int)V.size()&&sum<=(n-1)/2;++i)
		++tot,sum+=size[V[i]];
	for(reg int i=1;i<(int)V.size();++i)
		GetAns(V[i],root,sum-max(size[V[i]],size[V[tot]]));
	for(reg int i=head[root];i;i=Next[i])
		if(!vis[to[i]])
			GetAns(to[i],root,sum-size[V[tot]]);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i]<=1,i==n?'\n':' ');
	return;
}