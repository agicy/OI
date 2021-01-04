#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXP=40+5;
const int MAXQ=40+5;
const int MAXR=40+5;
const int MAXV=MAXP*MAXQ*MAXR;
const int MAXE=2*(MAXV+MAXP*MAXQ*2+MAXV);
const int inf=0x3f3f3f3f;

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

inline bool bfs(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int p,q,r,d;

inline int getId(reg int i,reg int j,reg int k){
	return (i-1)*p*q+(j-1)*q+k;
}

int main(void){
	p=read(),q=read(),r=read();
	d=read();
	reg int pq=p*q,dpq=d*p*q;
	reg int s=0,t=(r+1)*p*q+1;
	for(reg int i=1,Id=0,pId=pq;i<=r;++i)
		for(reg int j=1;j<=p;++j)
			for(reg int k=1;k<=q;++k){
				static int v;
				v=read();
				Add_Tube(++Id,++pId,v);
			}
	for(reg int i=d+1,Id=dpq,pId=0;i<=r+1;++i)
		for(reg int j=1;j<=p;++j)
			for(reg int k=1;k<=q;++k){
				++Id,++pId;
				const int dx[]={-1,0,0,1};
				const int dy[]={0,-1,1,0};
				const int dd[]={-q,-1,1,q};
				for(reg int l=0;l<4;++l){
					reg int fx=j+dx[l],fy=k+dy[l];
					if(1<=fx&&fx<=p&&1<=fy&&fy<=q)
						Add_Tube(Id,pId+dd[l],inf);
				}
			}
	for(reg int i=1,Id=0,rId=r*pq;i<=p;++i)
		for(reg int j=1;j<=q;++j){
			++Id,++rId;
			Add_Tube(s,Id,inf),Add_Tube(rId,t,inf);
		}
	reg int ans=dinic(s,t);
	printf("%d\n",ans);
	return 0;
}