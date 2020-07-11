#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X7FFFFFFF
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

const int MAXN=600+5;
const int MAXM=MAXN*(MAXN-1)/2;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,len);
	return;
}

int n,m;

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,c;
		u=read(),v=read(),c=read();
		Add_Tube(u,v,c);
	}
	return;
}

int dep[MAXN];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i])
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXN];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

int W[MAXM<<1];
bool vis[MAXN];
int p[MAXN];

inline void DFS(reg int ID){
	vis[ID]=true;
	for(reg int i=head[ID];i;i=Next[i])
		if(!vis[to[i]]&&w[i]>0)
			DFS(to[i]);
	return;
}

inline void Work(void){
	for(reg int i=1;i<=cnt;++i)
		W[i]=w[i];
	for(reg int i=2;i<=n;++i)
		p[i]=1;
	int ans=INF;
	for(reg int i=2;i<=n;++i){
		reg int s=i,t=p[i];
		for(reg int j=1;j<=cnt;++j)
			w[j]=W[j];
		int f=Dinic(s,t);
		memset(vis,false,sizeof(vis));
		ans=min(ans,f);
		DFS(s);
		for(reg int j=i;j<=n;++j)
			if(vis[j]&&p[j]==t)
				p[j]=s;
	}
	printf("%d\n",ans);
	return;
}
