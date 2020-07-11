#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=35+5;
const int MAXP=35+5;
const int MAXQ=35+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,p,q,s,t;
int a[MAXP][MAXQ];

inline int GetID(reg int i,reg int j){
	return (i-1)*q+j;
}

inline void Read(void){
	n=read(),q=read(),p=read(),s=GetID(1,1),t=GetID(p,q);
	for(reg int i=1;i<=p;++i)
		for(reg int j=1;j<=q;++j)
			a[i][j]=read();
	return;
}

int cnt=1,head[MAXP*MAXQ],to[(MAXP*MAXQ*2)<<1],w[(MAXP*MAXQ*2)<<1],Next[(MAXP*MAXQ*2)<<1];

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

inline pair<int,int> GetIJ(reg int ID){
	return make_pair((ID-((ID-1)%q+1))/q+1,((ID-1)%q+1));
}

int val[MAXP*MAXQ];
int W[(MAXP*MAXQ*2)<<1];
bool inque[MAXP*MAXQ];
int dis[MAXP*MAXQ];
queue<int> Q;

inline bool SPFA(int s,reg int t){
	memset(inque,false,sizeof(inque));
	memset(dis,-1,sizeof(dis));
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=val[s],Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]<dis[ID]+val[to[i]]&&w[i]>0){
				dis[to[i]]=dis[ID]+val[to[i]];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
	}
	return dis[t]!=-1;
}

int Cost;
bool vis[MAXP*MAXQ];
int cur[MAXP*MAXQ];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		Cost+=lim*dis[ID];
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dis[to[i]]==dis[ID]+val[to[i]]&&w[i]>0&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(w[i],lim-flow));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	vis[ID]=false;
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(res!=1&&SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,1);
	}
	return res;
}

inline bool check(reg int i,reg int j){
	return 1<=i&&i<=p&&1<=j&&j<=q&&a[i][j]!=1;
}

stack<int> S;

inline void Work(void){
	for(reg int i=1;i<=p;++i)
		for(reg int j=1;j<=q;++j)
			if(a[i][j]!=1){
				const int dx[]={0,+1};
				const int dy[]={+1,0};
				for(reg int k=0;k<2;++k){
					reg int fx=i+dx[k],fy=j+dy[k];
					if(check(fx,fy))
						Add_Tube(GetID(i,j),GetID(fx,fy),1);
				}
				val[GetID(i,j)]=(a[i][j]==2);
			}
	memcpy(W,w,sizeof(w));
	for(reg int i=1;i<=n;++i){
		memcpy(w,W,sizeof(W));
		Dinic(s,t);
		reg int ID=t;
		while(!S.empty())S.pop();
		while(true){
			if(val[ID])
				val[ID]=0;
			if(ID==s)
				break;
			pair<int,int> P=GetIJ(ID);
			for(reg int i=head[ID];i;i=Next[i])
				if(w[i]&&to[i]<ID){
					S.push(P.second>GetIJ(to[i]).second);
					ID=to[i];
					break;
				}
		}
		while(!S.empty()){
			printf("%d %d\n",i,S.top());
			S.pop();
		}
	}
	return;
}
