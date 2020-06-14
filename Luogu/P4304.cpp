#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
//static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200+5;
const int MAXV=MAXN*MAXN;
const int MAXE=(MAXN*MAXN*2+MAXN*MAXN*2)*2;

int n;
int M[MAXN][MAXN];

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

inline bool check(reg int i,reg int j){
	return 1<=i&&i<=n&&1<=j&&j<=n&&M[i][j]==0;
}

inline int GetID(reg int i,reg int j){
	return (i-1)*n+j;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			scanf("%1d",&M[i][j]);
	reg int s=0,t=n*n+1,ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			if(!M[i][j]){
				++ans;
				if((i+j)&1){
					Add_Tube(s,GetID(i,j),1);
					const int dx[]={-2,-2,-1,-1,1,1,2,2};
					const int dy[]={-1,1,-2,2,-2,2,-1,1};
					for(reg int k=0;k<8;++k){
						reg int fx=i+dx[k],fy=j+dy[k];
						if(check(fx,fy))
							Add_Tube(GetID(i,j),GetID(fx,fy),1);
					}
				}
				else
					Add_Tube(GetID(i,j),t,1);
			}
		}
	printf("%d\n",ans-Dinic(s,t));
	return 0;
}