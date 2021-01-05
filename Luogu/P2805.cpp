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

const int MAXN=20+5;
const int MAXM=30+5;
const int inf=0x3f3f3f3f;

namespace Graph{
	const int MAXV=MAXN*MAXM;
	const int MAXE=MAXN*MAXM*MAXN*MAXM;
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	int indeg[MAXV];
	inline void Add_Edge(reg int u,reg int v){
		++indeg[v];
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

namespace Network{
	const int MAXV=MAXN*MAXM;
	const int MAXE=(MAXV+MAXN*MAXM*(MAXN*MAXM-1)/2)*2;
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
		memset(dep,-1,sizeof(dep));
		reg int h=0,ta=0;
		dep[s]=1,Q[ta++]=s;
		while(h<ta){
			reg int u=Q[h++];
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]){
					dep[v]=dep[u]+1;
					Q[ta++]=v;
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

int n,m;
int sco[MAXN][MAXM];
vector<pair<int,int>/**/> att[MAXN][MAXM];

inline int getId(reg int i,reg int j){
	return i*m+j+1;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i){
		for(reg int j=0;j<m;++j){
			sco[i][j]=read();
			static int w;
			w=read();
			att[i][j].resize(w);
			while(w--){
				static int r,c;
				r=read(),c=read();
				att[i][j][w]=make_pair(r,c);
			}
		}
	}
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j){
			if(j<m-1)
				Graph::Add_Edge(getId(i,j+1),getId(i,j));
			for(vector<pair<int,int>/**/>::iterator it=att[i][j].begin();it!=att[i][j].end();++it)
				Graph::Add_Edge(getId(i,j),getId(it->first,it->second));
		}
	using Graph::indeg;
	queue<int> Q;
	for(int i=1;i<=n*m;++i)
		if(!indeg[i])
			Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=Graph::head[u];i;i=Graph::Next[i]){
			int v=Graph::to[i];
			--indeg[v];
			if(!indeg[v])
				Q.push(v);
		}
	}
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j)
			if(!indeg[getId(i,j)]){
				if(j<m-1&&!indeg[getId(i,j+1)])
					Network::Add_Tube(getId(i,j),getId(i,j+1),inf);
				for(vector<pair<int,int>/**/>::iterator it=att[i][j].begin();it!=att[i][j].end();++it)
					if(!indeg[getId(it->first,it->second)])
						Network::Add_Tube(getId(it->first,it->second),getId(i,j),inf);
			}
	reg int s=0,t=n*m+1;
	reg int sum=0;
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j)
			if(!indeg[getId(i,j)]){
				if(sco[i][j]>0){
					Network::Add_Tube(s,getId(i,j),sco[i][j]);
					sum+=sco[i][j];
				}
				else
					Network::Add_Tube(getId(i,j),t,-sco[i][j]);
			}
	reg int flow=Network::dinic(s,t);
	printf("%d\n",sum-flow);
	return 0;
}