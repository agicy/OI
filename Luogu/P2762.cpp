#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;

bool newline;

inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	if(ch=='\r'||ch=='\n')
		newline=true;
	return f?-res:res;
}

const int MAXN=50+5;
const int MAXM=50+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int m,n,s,t;
int cnt=-1,head[MAXN+MAXM+2],to[(MAXN*MAXM+MAXN+MAXM)*2],w[(MAXN*MAXM+MAXN+MAXM)*2],Next[(MAXN*MAXM+MAXN+MAXM)*2];
int ans;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	m=read(),n=read();
	memset(head,-1,sizeof(head));
	s=0,t=n+m+1;
	for(reg int i=1;i<=m;++i){
		static int w;
		w=read();
		ans+=w;
		Add_Edge(s,i,w);
		Add_Edge(i,s,0);
		newline=false;
		while(!newline){
			reg int x=read();
			Add_Edge(i,x+m,INF);
			Add_Edge(x+m,i,0);
		}
	}
	for(reg int i=1;i<=n;++i){
		static int w;
		w=read();
		Add_Edge(m+i,t,w);
		Add_Edge(t,m+i,0);
	}
	return;
}

int dep[MAXN+MAXM+2];

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

int cur[MAXN+MAXM+2];

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
	ans-=Dinic(s,t);
	for(reg int i=1;i<=m;++i)
		if(dep[i]>0)
			printf("%d ",i);
	putchar('\n');
	for(reg int i=1;i<=n;++i)
		if(dep[m+i]>0)
			printf("%d ",i);
	putchar('\n');
	printf("%d\n",ans);
	return;
}
