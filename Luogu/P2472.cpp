#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F

const int MAXR=20+5;
const int MAXC=20+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int r,c,d;
int s,t;
char h[MAXR][MAXC];
char M[MAXR][MAXC];
int sum;

inline int GetID(reg int k,reg int i,reg int j){
	return k*r*c+(i-1)*c+j;
}

int cnt=1,head[MAXR*MAXC*2],to[(MAXR*MAXC*3+MAXR*MAXC*MAXR*MAXC)<<1],w[(MAXR*MAXC*3+MAXR*MAXC*MAXR*MAXC)<<1],Next[(MAXR*MAXC*3+MAXR*MAXC*MAXR*MAXC)<<1];

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
	scanf("%d%d%d",&r,&c,&d);
	s=0,t=2*r*c+1;
	for(reg int i=1;i<=r;++i){
		scanf("%s",h[i]+1);
		for(reg int j=1;j<=c;++j){
			h[i][j]-='0';
			if(h[i][j])
				Add_Tube(GetID(0,i,j),GetID(1,i,j),h[i][j]);
		}
	}
	for(reg int i=1;i<=r;++i){
		scanf("%s",M[i]+1);
		for(reg int j=1;j<=c;++j)
			if(M[i][j]=='L'){
				Add_Tube(s,GetID(0,i,j),1);
				++sum;
			}
	}
	return;
}

int dep[MAXR*MAXC*2];
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

int cur[MAXR*MAXC*2];

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

inline int GetDis(reg int x1,reg int y1,reg int x2,reg int y2){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

inline void Work(void){
	for(reg int i=1;i<=r;++i)
		for(reg int j=1;j<=c;++j)
			if(h[i][j])
				for(reg int k=max(1,i-d);k<=min(r,i+d);++k)
					for(reg int l=max(1,j-d);l<=min(c,j+d);++l)
						if(i!=k||j!=l)
							if(GetDis(i,j,k,l)<=d*d&&h[k][l])
								Add_Tube(GetID(1,i,j),GetID(0,k,l),INF);
	for(reg int i=1;i<=r;++i)
		for(reg int j=1;j<=c;++j)
			if(h[i][j]&&(i-d<1||r<i+d||j-d<1||c<j+d))
				Add_Tube(GetID(1,i,j),t,INF);
	reg int ans=sum-Dinic(s,t);
	printf("%d\n",ans);
	return;
}