#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=500+5;
const int MAXM=500+5;
const int MAXV=MAXN+MAXM;
const int MAXE=2e6+5;
const int inf=0x3f3f3f3f;
const int MAXA=1e7+5;
const int MAXPCNT=664579+1;

bool vis[MAXA];
int tot,prime[MAXPCNT];
int las[MAXA];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i,las[i]=tot;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			las[i*prime[j]]=j;
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

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
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	reg int head_=0,tail_=0;
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q[tail_++]=s;
	while(head_<tail_){
		reg int u=Q[head_++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[tail_++]=v;
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
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int m,n;
int a[MAXM],b[MAXN];
vector<int> V[MAXPCNT];

int main(void){
	Init(1e7);
	reg int t=read();
	while(t--){
		cnt=1,memset(head,0,sizeof(head));
		for(reg int i=1;i<=tot;++i)
			V[i].clear();
		m=read(),n=read();
		for(reg int i=1;i<=m;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			b[i]=read();
		for(int i=1;i<=n;++i){
			reg int tmp=b[i];
			while(tmp!=1){
				V[las[tmp]].push_back(i);
				tmp/=prime[las[tmp]];
			}
		}
		for(reg int i=1;i<=m;++i){
			reg int tmp=a[i];
			while(tmp!=1){
				for(int v:V[las[tmp]])
					Add_Tube(i,v+m,1);
				tmp/=prime[las[tmp]];
			}
		}
		reg int s=0,t=n+m+1;
		for(reg int i=1;i<=m;++i)
			Add_Tube(s,i,1);
		for(reg int i=1;i<=n;++i)
			Add_Tube(i+m,t,+1);
		printf("%d\n",dinic(s,t));
	}
	return 0;
}