#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F

const int MAXN=1000+5;
const int MAXv=MAXN*(MAXN-1)/2;
const int MAXV=2*MAXN;
const int MAXE=(MAXN+MAXv)*2;

map<string,int> M;

int n,v;
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
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXV];
int dis[MAXV];
queue<int> Q;

inline bool SPFA(int s,reg int t){
	memset(inque,false,sizeof(inque));
	fill(dis,dis+t+1,-INF);
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]<dis[ID]+p[i]&&w[i]>0){
				dis[to[i]]=dis[ID]+p[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
	}
	return dis[t]!=-INF;
}

bool vis[MAXV];
int cur[MAXV];
int Cost;

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		Cost+=dis[t]*lim;
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dis[to[i]]==dis[ID]+p[i]&&w[i]>0&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(lim==flow)
					break;
			}
		}
	vis[ID]=false;
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

string str[MAXN];

inline void DFS1(reg int ID){
	cout<<str[ID]<<endl;
	vis[ID]=true;
	for(reg int i=head[ID];i;i=Next[i])
		if(n+1<=to[i]&&to[i]<=2*n&&w[i]==0&&!vis[to[i]-n]){
			DFS1(to[i]-n);
			break;
		}
	return;
}

inline void DFS2(reg int ID){
	vis[ID]=true;
	for(reg int i=head[ID];i;i=Next[i])
		if(n+1<=to[i]&&to[i]<=2*n&&w[i]==0&&!vis[to[i]-n])
			DFS2(to[i]-n);
	cout<<str[ID]<<endl;
	return;
}

int main(void){
	scanf("%d%d",&n,&v);
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i){
		cin>>str[i];
		M[str[i]]=i;
	}
	reg bool flag=false;
	for(reg int i=1;i<=v;++i){
		static string x,y;
		cin>>x>>y;
		int ix=M[x],iy=M[y];
		if(ix>iy)
			swap(ix,iy);
		if(ix==1&&iy==n)
			flag=true;
		Add_Tube(ix,iy+n,1,0);
	}
	Add_Tube(s,n+1,INF,0);
	Add_Tube(n,t,INF,0);
	for(reg int i=1;i<=n;++i)
		if(i!=1&&i!=n)
			Add_Tube(i+n,i,1,1);
		else
			Add_Tube(i+n,i,2,1);
	reg int flow=Dinic(s,t);
	if(flow==2){
		printf("%d\n",Cost-2);
		memset(vis,0,sizeof(vis));
		DFS1(1);
		DFS2(1);
	}
	else if(flow==1&&flag){
		puts("2");
		cout<<str[1]<<endl<<str[n]<<endl<<str[1]<<endl;
	}
	else
		puts("No Solution!");
	return 0;
}