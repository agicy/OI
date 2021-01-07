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

const int MAXN=100+5;
const int MAXM=100+5;
const int MAXS=1e5+5;
const int MAXV=MAXN;
const int MAXE=2*(MAXN+MAXM);
const int inf=0x3f3f3f3f;

bool vis[MAXS];
int tot,prime[MAXS];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
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

int n,m;
int a[MAXN];
vector<pair<int,int>/**/> V[MAXS];
vector<int> G[MAXN];
bool ext[MAXS];

inline int solve(reg int id){
	cnt=1,memset(head,0,sizeof(head));
	reg int s=0,t=n+1;
	for(vector<pair<int,int>/**/>::iterator it=V[id].begin();it!=V[id].end();++it)
		if(it->first&1)
			Add_Tube(s,it->first,it->second);
		else
			Add_Tube(it->first,t,it->second);
	for(reg int i=1;i<=n;i+=2)
		for(vector<int>::iterator it=G[i].begin();it!=G[i].end();++it)
			Add_Tube(i,*it,inf);
	return dinic(s,t);
}

map<int,int> M;
vector<int> exV[MAXN];

inline int exsolve(reg int id){
	cnt=1,memset(head,0,sizeof(head));
	reg int s=0,t=n+1;
	for(vector<int>::iterator it=exV[id].begin();it!=exV[id].end();++it)
		if(*it&1)
			Add_Tube(s,*it,1);
		else
			Add_Tube(*it,t,1);
	for(reg int i=1;i<=n;i+=2)
		for(vector<int>::iterator it=G[i].begin();it!=G[i].end();++it)
			Add_Tube(i,*it,inf);
	return dinic(s,t);
}

int main(void){
	Init(1e5);
	n=read(),m=read();
	reg int extot=0;
	for(int i=1;i<=n;++i){
		a[i]=read();
		for(reg int j=1;j<=tot&&prime[j]<=a[i];++j)
			if(a[i]%prime[j]==0){
				ext[j]=true;
				int cnt=0;
				while(a[i]%prime[j]==0)
					++cnt,a[i]/=prime[j];
				V[j].push_back(make_pair(i,cnt));
			}
		if(a[i]>1){
			if(!M[a[i]])
				M[a[i]]=++extot;
			exV[M[a[i]]].push_back(i);
		}
	}
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		if(a&1)
			G[a].push_back(b);
		else
			G[b].push_back(a);
	}
	reg int ans=0;
	for(reg int i=1;i<=tot;++i)
		if(ext[i])
			ans+=solve(i);
	for(reg int i=1;i<=extot;++i)
		ans+=exsolve(i);
	printf("%d\n",ans);
	return 0;
}