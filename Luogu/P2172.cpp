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

const int MAXM=50+5;
const int MAXN=50+5;
const int MAXV=MAXN*MAXM*2;
const int MAXE=MAXN*MAXM*6;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int m,n,R,C;
char M[MAXM][MAXM];

inline void Read(void){
	m=read(),n=read(),R=read(),C=read();
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			cin>>M[i][j];
	return;
}

inline int GetID(reg int i,reg int j,reg int k){
	return (i-1)*n+j+k*m*n;
}

inline bool check(reg int i,reg int j){
	return 1<=i&&i<=m&&1<=j&&j<=n&&M[i][j]=='.';
}

int cnt=1,head[MAXV],to[MAXE<<1],w[MAXE<<1],Next[MAXE<<1];

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

inline void Work(void){
	reg int sum=0;
	reg int s=GetID(m,n,1)+1+1,t=s+1;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			if(M[i][j]=='.'){
				++sum;
				Add_Tube(s,GetID(i,j,0),1);
				Add_Tube(GetID(i,j,1),t,1);
				const int dx[]={R,R,C,C};
				const int dy[]={-C,C,-R,R};
				for(reg int k=0;k<4;++k){
					reg int fx=i+dx[k],fy=j+dy[k];
					if(check(fx,fy))
						Add_Tube(GetID(i,j,0),GetID(fx,fy,1),1);
				}
			}
	reg int ans=Dinic(s,t);
	printf("%d\n",sum-ans);
	return;
}