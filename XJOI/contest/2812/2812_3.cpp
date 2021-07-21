#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e3+5;
const int MAXM=6e3+5;
const int inf=0x3f3f3f3f;

namespace Network{
	const int MAXV=MAXN+MAXM;
	const int MAXE=(MAXM+MAXN+MAXM*2)*2;
	int cnt,head[MAXV],to[MAXE],w[MAXE],nxt[MAXE];
	inline void init(reg int s,reg int t){
		cnt=1,memset(head,0,sizeof(int)*(t-s+1));
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg int lim){
		nxt[++cnt]=head[u];
		to[cnt]=v,w[cnt]=lim;
		head[u]=cnt;
		return;
	}
	inline int Add_Tube(reg int u,reg int v,reg int lim){
		Add_Edge(u,v,lim),Add_Edge(v,u,0);
		return cnt-1;
	}
	int dep[MAXV];
	int cur[MAXV];
	inline bool bfs(reg int s,reg int t){
		memset(dep,-1,sizeof(int)*(t-s+1));
		reg int _head=0,_tail=0;
		static int Q[MAXV];
		dep[s]=1,Q[_tail++]=s;
		while(_head<_tail){
			reg int u=Q[_head++];
			cur[u]=head[u];
			for(reg int i=head[u];i;i=nxt[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i])
					dep[v]=dep[u]+1,Q[_tail++]=v;
			}
		}
		return dep[t]!=-1;
	}
	inline int dfs(reg int u,reg int t,reg int lim){
		if(u==t)
			return lim;
		reg int flow=0;
		for(reg int& i=cur[u];i;i=nxt[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+1&&w[i]){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f,w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		return flow;
	}
	inline int dinic(reg int s,reg int t){
		reg int res=0;
		while(bfs(s,t))
			res+=dfs(s,t,inf);
		return res;
	}
}

struct Edge{
	int u,v;
	inline bool operator!=(const Edge& a)const{
		return u!=a.u||v!=a.v;
	}
	inline bool operator<(const Edge& a)const{
		return u<a.u||(u==a.u&&v<a.v);
	}
};

int n,m,lim;
Edge e[MAXM];
int val[MAXM];
int mat[MAXN];

bool ed;

int main(void){
	n=read(),m=read(),lim=read();
	for(reg int i=1;i<=m;++i){
		e[i].u=read(),e[i].v=read();
		if(e[i].u>e[i].v)
			swap(e[i].u,e[i].v);
	}
	sort(e+1,e+m+1);
	reg int tot=0;
	static Edge E[MAXM];
	for(reg int i=1;i<=m;++i)
		if(e[i]!=e[i-1]){
			E[++tot]=e[i];
			val[tot]=1;
		}
		else
			++val[tot];
	reg int s=0,t=n+m+1;
	Network::init(s,t);
	for(reg int i=1;i<=n;++i)
		mat[i]=Network::Add_Tube(s,i,lim);
	for(reg int i=1;i<=tot;++i)
		Network::Add_Tube(i+n,t,val[i]),Network::Add_Tube(E[i].u,i+n,inf),Network::Add_Tube(E[i].v,i+n,inf);
	static int bacW[Network::MAXE];
	memcpy(bacW+1,Network::w+1,sizeof(int)*(Network::cnt));
	for(reg int id=1;id<=n;++id){
		Network::w[mat[id]]=0;
		if(m-Network::dinic(s,t)>0){
			puts("Yes");
			return 0;
		}
		memcpy(Network::w+1,bacW+1,sizeof(int)*(Network::cnt));
	}
	puts("No");
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}