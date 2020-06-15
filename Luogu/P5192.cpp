#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=365+5;
const int MAXM=1000+5;
const int MAXV=MAXN+MAXM;
const int MAXE=MAXN*MAXM;

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

int cur[MAXV];

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

int in[MAXV],out[MAXV];

inline void Init(void){
	cnt=1;
	memset(head,0,sizeof(head));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	return;
}

int n,m;
int G[MAXM];

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		Init();
		reg int s1=n+m+1,t1=n+m+2,s2=n+m+3,t2=n+m+4;
		reg int s=s2,t=t2;
		for(reg int i=1;i<=m;++i){
			scanf("%d",&G[i]);
			in[t1]+=G[i],out[n+i]+=G[i];
			Add_Tube(n+i,t1,INF-G[i]);
		}
		for(reg int i=1;i<=n;++i){
			static int c,d;
			scanf("%d%d",&c,&d);
			Add_Tube(s1,i,d);
			for(reg int j=1;j<=c;++j){
				static int T,L,R;
				scanf("%d%d%d",&T,&L,&R);
				++T;
				in[n+T]+=L,out[i]+=L;
				Add_Tube(i,n+T,R-L);
			}
		}
		reg int sum=0;
		for(reg int i=1;i<=n+m+2;++i)
			if(in[i]>out[i])
				Add_Tube(s,i,in[i]-out[i]),sum+=in[i]-out[i];
			else
				Add_Tube(i,t,out[i]-in[i]);
		Add_Tube(t1,s1,INF);
		if(Dinic(s,t)!=sum)
			puts("-1\n");
		else{
			reg int ans=w[cnt];
			w[cnt]=w[cnt^1]=0;
			s=s1,t=t1;
			ans+=Dinic(s,t);
			printf("%d\n\n",ans);
		}
	}
	return 0;
}