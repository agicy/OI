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

const int MAXN=100+5;
const int MAXF=100+5;
const int MAXD=100+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,f,d,s,t;
int cnt=1,head[MAXN*2+MAXF+MAXD],to[(MAXN*MAXF+MAXN*MAXD+MAXN+MAXF+MAXD)*2],w[(MAXN*MAXF+MAXN*MAXD+MAXN+MAXF+MAXD)*2],Next[(MAXN*MAXF+MAXN*MAXD+MAXN+MAXF+MAXD)*2];

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

inline void Read(void){
	n=read(),f=read(),d=read();
	s=0,t=2*n+f+d+1;
	for(reg int i=1;i<=n;++i){
		static int fi,di;
		fi=read(),di=read();
		for(reg int j=1;j<=fi;++j){
			static int x;
			x=read();
			Add_Tube(x+2*n,i,1);
		}
		for(reg int j=1;j<=di;++j){
			static int x;
			x=read();
			Add_Tube(i+n,x+2*n+f,1);
		}
	}
	for(reg int i=1;i<=n;++i)
		Add_Tube(i,i+n,1);
	for(reg int i=1;i<=f;++i)
		Add_Tube(s,2*n+i,1);
	for(reg int i=1;i<=d;++i)
		Add_Tube(2*n+f+i,t,1);
	return;
}

int dep[MAXN*2+MAXF+MAXD];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i])
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXN*2+MAXF+MAXD];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i]){
		if(dep[to[i]]==dep[ID]+1&&w[i]){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f>0){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(lim==flow)
					break;
			}
		}
	}
	return flow;
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
	reg int ans=Dinic(s,t);
	printf("%d\n",ans);
	return;
}
