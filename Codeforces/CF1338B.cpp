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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int Deg[MAXN];
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
		++Deg[u],++Deg[v];
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

int ans1,ans2;
bool vis[2];
int dep[MAXN];

inline int DFS(reg int ID,reg int father){
	if(Deg[ID]==1){
		vis[dep[ID]&1]=true;
		return 1;
	}
	reg int sum=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dep[to[i]]=dep[ID]+1;
			sum+=DFS(to[i],ID);
		}
	ans2-=max(0,sum-1);
	return 0;
}

inline void Work(void){
	reg int root=-1;
	for(reg int i=1;i<=n;++i)
		if(Deg[i]>1){
			root=i;
			break;
		}
	ans2=(n-1);
	DFS(root,0);
	ans1=(vis[0]&&vis[1])?3:1;
	printf("%d %d\n",ans1,ans2);
	return;
}
