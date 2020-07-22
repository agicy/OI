#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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
const int MAXV=MAXN*2;
const int MAXE=(MAXN*4)*2;

int n,K;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	printf("%d %d %d\n",u,v,len);
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXV];
int dis[MAXV];
queue<int> Q;

inline bool SPFA(int s,reg int t){
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+p[i]&&w[i]>0){
				dis[v]=dis[u]+p[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return dis[t]!=INF;
}

int Cost;
bool vis[MAXV];
int cur[MAXV];

inline int DFS(reg int u,reg int t,reg int lim){
	if(u==t){
		Cost+=lim*dis[t];
		return lim;
	}
	vis[u]=true;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]==dis[u]+p[i]&&w[i]>0&&!vis[v]){
			reg int f=DFS(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	vis[u]=false;
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

struct Node{
	int lx,ly,rx,ry;
	inline void Read(void){
		lx=read(),ly=read(),rx=read(),ry=read();
		if(lx>rx)
			swap(lx,rx);
		return;
	}
};

Node L[MAXN];
vector<int> V;

inline int sqr(reg int x){
	return x*x;
}

inline int GetLen(const Node& a){
	return floor(sqrt(sqr(a.lx-a.rx)+sqr(a.ly-a.rx)));
}

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i){
		L[i].Read();
		V.push_back(L[i].lx);
		V.push_back(L[i].rx);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int m=V.size();
	reg int s=0,t=2*m+1;
	for(reg int i=1;i<=m;++i)
		Add_Tube(i,i+m,K,0);
	for(reg int i=1;i<m;++i)
		Add_Tube(i+m,i+1,K,0);
	for(reg int i=1;i<=n;++i){
		reg int l=lower_bound(V.begin(),V.end(),L[i].lx)-V.begin()+1;
		reg int r=lower_bound(V.begin(),V.end(),L[i].rx)-V.begin()+1;
		if(l==r)
			Add_Tube(l,r+m,1,-GetLen(L[i]));
		else
			Add_Tube(l+m,r,1,-GetLen(L[i]));
	}
	Add_Tube(s,1,K,0);
	Add_Tube(2*m,t,K,0);
	Dinic(s,t);
	printf("%d\n",-Cost);
	return 0;
}
