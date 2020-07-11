#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=500+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,s,t;
int a[MAXN];
int cnt=1,head[MAXN<<1],to[MAXN*MAXN*10],w[MAXN*MAXN*10],Next[MAXN*MAXN*10];

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

inline void Read(void){
	n=read(),s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

int dp[MAXN];
int dep[MAXN<<1];
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

int cur[MAXN<<1];

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

inline void Work(void){
	for(reg int i=1;i<=n;++i){
		dp[i]=1;
		for(reg int j=1;j<i;++j)
			if(a[j]<=a[i])
				dp[i]=max(dp[i],dp[j]+1);
	}
	int len=0;
	for(reg int i=1;i<=n;++i)
		len=max(len,dp[i]);
	printf("%d\n",len);
	for(reg int i=1;i<=n;++i){
		if(dp[i]==1)
			Add_Tube(s,i,1);
		if(dp[i]==len)
			Add_Tube(i+n,t,1);
	}
	for(reg int i=1;i<=n;++i)
		Add_Tube(i,i+n,1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<i;++j)
			if(a[j]<=a[i]&&dp[j]+1==dp[i])
				Add_Tube(j+n,i,1);
	reg int ans=Dinic(s,t);
	printf("%d\n",ans);
	Add_Tube(s,1,INF);
	Add_Tube(1,1+n,INF);
	if(dp[n]==len){
		Add_Tube(n,n+n,INF);
		Add_Tube(n+n,t,INF);
	}
	ans+=Dinic(s,t);
	printf("%d\n",n==1?1:ans);
	return;
}
