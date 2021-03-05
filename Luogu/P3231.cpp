#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e3+5;
const int MAXV=2*MAXN;
const int MAXE=(MAXN*2+MAXN*2)*2;
const int inf=0x3f3f3f3f;

int a,b,c;
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
pair<int,int> e[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	fill(dep+s,dep+t+1,-1);
	reg int _head=0,_tail=0;
	dep[s]=1,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[_tail++]=v;
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(bfs(s,t)){
		for(reg int i=s;i<=t;++i)
			cur[i]=head[i];
		res+=dfs(s,t,inf);
	}
	return res;
}

bool vis[MAXN];
int tot,V[4][MAXN];

inline int solve(reg int S){
	reg int res=0;
	for(reg int i=0;i<a;++i)
		if((S>>i)&1)
			vis[i+1]=false,++res;
		else
			vis[i+1]=true;
	reg int Max=0,siz=0;
	for(reg int i=1;i<=tot;++i)
		if(vis[V[1][i]])
			e[++siz]=make_pair(V[2][i],V[3][i]);
	for(reg int i=1;i<=siz;++i)
		Max=max(Max,max(e[i].first,e[i].second));
	reg int s=0,t=Max*2+1;
	cnt=1,fill(head+s,head+t+1,0);
	for(reg int i=1;i<=Max;++i)
		Add_Tube(s,i,1),Add_Tube(i+Max,t,1);
	for(reg int i=1;i<=siz;++i)
		Add_Tube(e[i].first,e[i].second+Max,1);
	return res+dinic(s,t);
}

int main(void){
	reg int T=read();
	while(T--){
		tot=0;
		a=read(),b=read(),c=read();
		reg int Min=min(min(a,b),c);
		for(reg int i=1;i<=a;++i)
			for(reg int j=1;j<=b;++j)
				for(reg int k=1;k<=c;++k)
					if(read())
						V[1][++tot]=i,V[2][tot]=j,V[3][tot]=k;
		if(Min==b)
			swap(a,b),swap(V[1],V[2]);
		else if(Min==c)
			swap(a,c),swap(V[1],V[3]);
		reg int ans=Min;
		for(reg int i=0;i<(1<<a);++i)
			ans=min(ans,solve(i));
		printf("%d\n",ans);
	}
	return 0;
}