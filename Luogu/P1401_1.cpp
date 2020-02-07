#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=200+5;
const int MAXM=40000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,T;
int s,t;
int cnt=1,head[MAXN],to[MAXM<<2],w[MAXM<<2],Next[MAXM<<2];
vector<int> V;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Edge{
	int a,b,l;
	inline void Read(void){
		a=read(),b=read(),l=read();
		return;
	}
	inline bool operator<(const Edge& a){
		return l<a.l;
	}
};

Edge E[MAXM];

inline void Read(void){
	n=read(),m=read(),T=read();
	s=1,t=n;
	for(reg int i=1;i<=m;++i){
		E[i].Read();
		V.push_back(E[i].l);
	}
	return;
}

int dep[MAXN];

inline bool BFS(int s,reg int t){
	queue<int> Q;
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i!=-1;i=Next[i]){
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
		}
	}
	return dep[t]>0;
}

int cur[MAXN];

inline int DFS(reg int ID,reg int t,int lim){
	if(ID==t)
		return lim;
	for(int &i=cur[ID];i!=-1;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[ID]+1&&w[i]>0){
			reg int flow=DFS(v,t,min(lim,w[i]));
			if(flow){
				w[i]-=flow;
				w[i^1]+=flow;
				return flow;
			}
		}
	}
	return 0;
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
	sort(E+1,E+m+1);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	memset(head,-1,sizeof(head));
	reg int cnt=0;
	reg int p=1;
	for(reg int i=0;i<(int)V.size();++i){
		while(p<=m&&E[p].l<=V[i]){
			Add_Edge(E[p].a,E[p].b,1),Add_Edge(E[p].b,E[p].a,0);
			Add_Edge(E[p].b,E[p].a,1),Add_Edge(E[p].a,E[p].b,0);
			++p;
		}
		cnt+=Dinic(s,t);
		if(cnt>=T){
			printf("%d\n",V[i]);
			break;
		}
	}
	return;
}
