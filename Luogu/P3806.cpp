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

const int MAXN=10000+5;
const int MAXM=100+5;
const int MAXC=10000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int K[MAXM];

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
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Edge(a,b,c);
		Add_Edge(b,a,c);
	}
	for(reg int i=1;i<=m;++i)
		K[i]=read();
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

int tot,v[MAXN],dis[MAXN];

inline void DFS(reg int ID,reg int father){
	v[++tot]=dis[ID];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&!del[to[i]]){
			dis[to[i]]=dis[ID]+w[i];
			DFS(to[i],ID);
		}
	return;
}

bool ans[MAXM];
bool vis[MAXN*MAXC];
int Q[MAXN];

inline void Calc(reg int ID){
	reg int p=0;
	vis[0]=true;
	for(reg int i=head[ID];i;i=Next[i]){
		if(!del[to[i]]){
			tot=0;
			dis[to[i]]=w[i];
			DFS(to[i],ID);
			for(reg int i=1;i<=tot;++i)
				for(reg int j=1;j<=m;++j)
					if(v[i]<=K[j])
						ans[j]|=vis[K[j]-v[i]];
			for(reg int i=1;i<=tot;++i)
				vis[v[i]]=true,Q[++p]=v[i];
		}
	}
	for(reg int i=1;i<=p;++i)
		vis[Q[i]]=false;
	return;
}

inline void Solve(reg int ID){
	del[ID]=true;
	Calc(ID);
	for(reg int i=head[ID];i;i=Next[i]){
		if(!del[to[i]]){
			sum=size[to[i]];
			MaxSon[root=0]=INF;
			GetRoot(to[i],0);
			Solve(root);
		}
	}
	return;
}

inline void Work(void){
	MaxSon[root=0]=sum=n;
	GetRoot(1,0);
	Solve(root);
	for(reg int i=1;i<=m;++i)
		puts(ans[i]?"AYE":"NAY");
	return;
}
