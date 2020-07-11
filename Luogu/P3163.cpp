#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50+5;

inline void Read(void);
inline void Work(void);

int n;

int main(void){
	while(scanf("%d",&n)!=EOF){
		Read();
		Work();
	}
	return 0;
}

int s,t;
int a1,a2,an;
int b1,b2,bn;
int cnt,head[MAXN],to[(MAXN*MAXN)<<1],w[(MAXN*MAXN)<<1],Next[(MAXN*MAXN)<<1];

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

char M[MAXN][MAXN];

inline void Read(void){
	a1=read()+1,a2=read()+1,an=read(),b1=read()+1,b2=read()+1,bn=read();
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	return;
}

int dep[MAXN];
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

int cur[MAXN];

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

inline void Build(void){
	cnt=1;
	memset(head,0,sizeof(head));
	s=0,t=n+1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(i!=j)
				switch(M[i][j]){
					case 'N':Add_Tube(i,j,INF);break;
					case 'O':Add_Tube(i,j,2);break;
					default:break;
				}
	return;
}

inline void Work(void){
	Build();
	Add_Tube(s,a1,an*2),Add_Tube(a2,t,an*2);
	Add_Tube(s,b1,bn*2),Add_Tube(b2,t,bn*2);
	reg int ans1=Dinic(s,t);
	Build();
	Add_Tube(s,a1,an*2),Add_Tube(a2,t,an*2);
	Add_Tube(s,b2,bn*2),Add_Tube(b1,t,bn*2);
	reg int ans2=Dinic(s,t);
	puts(ans1==(an+bn)*2&&ans2==(an+bn)*2?"Yes":"No");
	return;
}
