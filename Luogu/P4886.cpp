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

const int MAXN=100000+5;
const int MAXM=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

struct Node{
	int u,v;
	inline Node(reg int u=0,reg int v=0):u(u),v(v){
		return;
	}
	inline void Read(void){
		u=read(),v=read();
		return;
	}
};

Node p[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	for(reg int i=1;i<=m;++i)
		p[i].Read();
	return;
}

int size[MAXN];
int root,MaxPart;
bool del[MAXN];

inline void GetRoot(reg int ID,reg int father,reg int sum){
	size[ID]=1;
	reg int MaxSon=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			GetRoot(to[i],ID,sum);
			size[ID]+=size[to[i]];
			MaxSon=max((int)MaxSon,size[to[i]]);
		}
	MaxSon=max((int)MaxSon,sum-size[ID]);
	if(MaxSon<MaxPart)
		root=ID;
	return;
}

int c[MAXN],dis[MAXN];

inline void DFS(reg int ID,reg int father,reg int color){
	c[ID]=color;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dis[to[i]]=dis[ID]+w[i];
			DFS(to[i],ID,color);
		}
	return;
}

int ans=INF;
int M[MAXM];

inline void Solve(reg int ID){
	if(del[ID]){
		printf("%d\n",ans);
		exit(0);
	}
	del[ID]=true,dis[ID]=c[ID]=0;
	for(reg int i=head[ID];i;i=Next[i]){
		dis[to[i]]=w[i];
		DFS(to[i],ID,to[i]);
	}
	reg int Max=0,tot=0;
	for(reg int i=1;i<=m;++i)
		if(dis[p[i].u]+dis[p[i].v]>Max){
			Max=dis[p[i].u]+dis[p[i].v];
			tot=0;
			M[++tot]=i;
		}
		else if(Max==dis[p[i].u]+dis[p[i].v])
			M[++tot]=i;
	ans=min(ans,(int)Max);
	reg int last=0;
	for(reg int i=1;i<=tot;++i){
		if(c[p[M[i]].u]!=c[p[M[i]].v]){
			printf("%d\n",ans);
			exit(0);
		}
		else if(!last)
			last=c[p[M[i]].u];
		else if(c[p[M[i]].u]!=last){
			printf("%d\n",ans);
			exit(0);
		}
	}
	root=last,MaxPart=INF;
	GetRoot(last,0,size[last]);
	Solve(root);
	return;
}

inline void Work(void){
	root=1,MaxPart=INF;
	GetRoot(1,0,n);
	Solve(root);
	printf("%d\n",ans);
	return;
}
