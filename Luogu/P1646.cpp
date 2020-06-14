#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 1e9
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXV=100000+5;
const int MAXE=5000000+5;

int n,m;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline int GetID(reg int i,reg int j){
	return (i-1)*m+j;
}

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
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

int cur[MAXV];

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

int main(void){
	n=read(),m=read();
	int s=0,t=n*m+2*n*(m-1)+2*(n-1)*m+1,cnt=n*m;
	int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			static int x;
			x=read();
			ans+=x;
			Add_Tube(s,GetID(i,j),x);
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			static int x;
			x=read();
			ans+=x;
			Add_Tube(GetID(i,j),t,x);
		}
	for(reg int i=1;i<=n-1;++i)
		for(reg int j=1;j<=m;++j){
			static int x;
			x=read();
			ans+=x;
			Add_Tube(s,++cnt,x);
			Add_Tube(cnt,GetID(i,j),INF);
			Add_Tube(cnt,GetID(i+1,j),INF);
		}
	for(reg int i=1;i<=n-1;++i)
		for(reg int j=1;j<=m;++j){
			static int x;
			x=read();
			ans+=x;
			Add_Tube(++cnt,t,x);
			Add_Tube(GetID(i,j),cnt,INF);
			Add_Tube(GetID(i+1,j),cnt,INF);
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m-1;++j){
			static int x;
			x=read();
			ans+=x;
			Add_Tube(s,++cnt,x);
			Add_Tube(cnt,GetID(i,j),INF);
			Add_Tube(cnt,GetID(i,j+1),INF);
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m-1;++j){
			static int x;
			x=read();
			ans+=x;
			Add_Tube(++cnt,t,x);
			Add_Tube(GetID(i,j),cnt,INF);
			Add_Tube(GetID(i,j+1),cnt,INF);
		}
	ans-=Dinic(s,t);
	printf("%d\n",ans);
	return 0;
}