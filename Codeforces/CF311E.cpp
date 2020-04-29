#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=10000+5;
const int MAXM=2000+5;
const int MAXK=10+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,g,s,t;
int a[MAXN];
int sum;
int cnt=1,head[MAXN+MAXM],to[(MAXN*MAXK+MAXN*2)<<1],w[(MAXN*MAXK+MAXN*2)<<1],Next[(MAXN*MAXK+MAXN*2)<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

inline void Read(void){
	n=read(),m=read(),g=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	s=0,t=n+m+1;
	for(reg int i=1;i<=n;++i){
		static int v;
		v=read();
		if(!a[i])
			Add_Tube(s,i,v);
		else
			Add_Tube(i,t,v);
	}
	for(reg int i=1;i<=m;++i){
		static int opt,w,k;
		opt=read(),w=read(),k=read();
		if(opt){
			for(reg int j=1;j<=k;++j){
				static int x;
				x=read();
				Add_Tube(x,n+i,INF);
			}
			opt=read();
			if(opt)
				Add_Tube(n+i,t,g+w);
			else
				Add_Tube(n+i,t,w);
		}
		else{
			for(reg int j=1;j<=k;++j){
				static int x;
				x=read();
				Add_Tube(n+i,x,INF);
			}
			opt=read();
			if(opt)
				Add_Tube(s,n+i,g+w);
			else
				Add_Tube(s,n+i,w);
		}
		sum+=w;
	}
	return;
}

int dep[MAXN+MAXM];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
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

int cur[MAXN+MAXM];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
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
	reg int ans=sum-Dinic(s,t);
	printf("%d\n",ans);
	return;
}
