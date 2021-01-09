#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=13+5;
const int MAXM=20+5;
const int MAXK=50+5;
const int MAXT=MAXN*MAXK;
const int MAXV=MAXT*MAXN;
const int MAXE=2*(MAXT*MAXN+MAXM*MAXN+MAXT*2);
const int inf=0x3f3f3f3f;

int n,m,k;
int h[MAXM],r[MAXM];
vector<int> S[MAXM];

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int l,reg int r){
		for(reg int i=l;i<=r;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

namespace Network{
	int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
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
}

inline int getId(reg int t,reg int id){
	return t*(n+2)+id;
}

inline int getPre(reg int t,reg int id){
	if(!(t%S[id].size()))
		return getId(t-1,S[id][S[id].size()-1]);
	else
		return getId(t-1,S[id][(t%S[id].size())-1]);
}

inline int getNow(reg int t,reg int id){
	return getId(t,S[id][t%S[id].size()]);
}

int main(void){
	n=read(),m=read(),k=read();
	UnionFind::Init(0,n+1);
	for(reg int i=1;i<=m;++i){
		h[i]=read(),r[i]=read();
		S[i].resize(r[i]);
		for(reg int j=0;j<r[i];++j){
			S[i][j]=read();
			if(S[i][j]==-1)
				S[i][j]=n+1;
			if(j)
				UnionFind::merge(S[i][j-1],S[i][j]);
		}
	}
	if(!UnionFind::search(0,n+1)){
		puts("0");
		exit(0);
	}
	reg int s=MAXV-2,t=MAXV-1;
	reg int sum=0;
	Network::Add_Tube(s,getId(0,0),inf);
	Network::Add_Tube(getId(0,n+1),t,inf);
	for(reg int T=1;T<=MAXT;++T){
		Network::Add_Tube(s,getId(T,0),inf);
		Network::Add_Tube(getId(T,n+1),t,inf);
		for(reg int i=0;i<=n+1;++i)
			Network::Add_Tube(getId(T-1,i),getId(T,i),inf);
		for(reg int i=1;i<=m;++i)
			Network::Add_Tube(getPre(T,i),getNow(T,i),h[i]);
		sum+=Network::dinic(s,t);
		if(sum>=k){
			printf("%d\n",T);
			break;
		}
	}
	return 0;
}