#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 2e9
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

const int MAXN=100+5;
const int MAXM=100+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int m,n;
ll ans;
int cnt=1,head[MAXN*MAXM+2+100],to[MAXN*2*MAXM*6],w[MAXN*2*MAXM*6],Next[MAXN*2*MAXM*6];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int ID[MAXM][MAXN];

inline void Read(void){
	m=read(),n=read();
	memset(head,-1,sizeof(head));
	int s=0,t=n*m+1;
	reg int cnt=0;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			ID[i][j]=++cnt;
	for(reg int i=1;i<=m;++i){
		for(reg int j=1;j<=n;++j){
			static int a;
			a=read();
			ans+=a;
			if((i+j)%2==0){
				Add_Edge(s,ID[i][j],a);
				Add_Edge(ID[i][j],s,0);
				const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
				for(reg int k=0;k<4;++k){
					reg int x=i+dx[k],y=j+dy[k];
					if(1<=x&&x<=m&&1<=y&&y<=n){
						Add_Edge(ID[i][j],ID[x][y],INF);
						Add_Edge(ID[x][y],ID[i][j],0);
					}
				}
			}
			else{
				Add_Edge(ID[i][j],t,a);
				Add_Edge(t,ID[i][j],0);
			}
		}
	}
	return;
}

int dep[MAXN*MAXM+2+100];
int cur[MAXN*MAXM+2+100];

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
	int s=0,t=n*m+1;
	ans-=Dinic(s,t);
	printf("%lld\n",ans);
	return;
}
