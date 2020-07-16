#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=300+5;
const int MAXV=2*MAXN;
const int MAXE=2*(MAXN*MAXN*2+2*MAXN+MAXN);

inline ll sqr(reg ll x){
	return x*x;
}

struct Round{
	int id;
	ll x,y,r;
	inline void Read(reg int i){
		id=i;
		x=read(),y=read(),r=read();
		return;
	}
};

struct Square{
	int id;
	ll x1,y1,x2,y2;
	inline void Read(reg int i){
		id=i;
		x1=read(),y1=read(),x2=read(),y2=read();
		return;
	}
};

Round R[MAXN];
Square S[MAXN];

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
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]>0){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int DFS(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]>0){
			reg int f=DFS(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
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

int cx,cy;

inline bool checkx(const Round& a,const Square& b){
	if(min(a.x,b.x1)!=b.x1||max(a.x,b.x2)!=b.x2)
		return false;
	if(min(a.y,b.y1)==b.y1&&max(a.y,b.y2)==b.y2)
		return true;
	return sqr(a.y-b.y1)<=sqr(a.r)||sqr(a.y-b.y2)<=sqr(a.r);
}

inline bool checky(const Round& a,const Square& b){
	if(min(a.y,b.y1)!=b.y1||max(a.y,b.y2)!=b.y2)
		return false;
	return sqr(a.x-b.x1)<=sqr(a.r)||sqr(a.x-b.x2)<=sqr(a.r);
}

inline bool checkp(const Round& b,const Square& a){
	reg ll r2=sqr(b.r);
	return (sqr(a.x1-b.x)+sqr(a.y1-b.y)<=r2||sqr(a.x1-b.x)+sqr(a.y2-b.y)<=r2||sqr(a.x2-b.x)+sqr(a.y1-b.y)<=r2||sqr(a.x2-b.x)+sqr(a.y2-b.y)<=r2);
}

inline bool check(const Round& b,const Square& a){
	return checkx(b,a)||checky(b,a)||checkp(b,a);
}

inline bool check(const Round& a,const Round& b){
	return sqr(a.r+b.r)>=sqr(a.x-b.x)+sqr(a.y-b.y);
}

inline bool check(const Square& a,const Square& b){
	reg bool fx=min(a.x2,b.x2)>=max(a.x1,b.x1);
	reg bool fy=min(a.y2,b.y2)>=max(a.y1,b.y1);
	return fx&&fy;
}

inline bool checkS(const Round& a){
	return cy<=a.y+a.r;
}

inline bool checkT(const Round& a){
	return a.y-a.r<=0;
}

inline bool checkS(const Square& a){
	return cy<=a.y2;
}

inline bool checkT(const Square& a){
	return a.y1<=0;
}

int n;

int main(void){
	cx=read(),cy=read();
	n=read();
	reg int cntR=0,cntS=0;
	for(reg int i=1;i<=n;++i){
		static int type;
		type=read();
		switch(type){
			case 1:{
				R[++cntR].Read(i);
				break;
			}
			case 2:{
				S[++cntS].Read(i);
				break;
			}
			default:break;
		}
	}
	for(reg int i=1;i<=n;++i)
		Add_Tube(i,i+n,1);
	for(reg int i=1;i<=cntR;++i)
		for(reg int j=1;j<=cntS;++j)
			if(check(R[i],S[j])){
				reg int a=R[i].id,b=S[j].id;
				Add_Tube(a+n,b,INF);
				Add_Tube(b+n,a,INF);
			}
	for(reg int i=1;i<=cntR;++i)
		for(reg int j=i+1;j<=cntR;++j)
			if(check(R[i],R[j])){
				reg int a=R[i].id,b=R[j].id;
				Add_Tube(a+n,b,INF);
				Add_Tube(b+n,a,INF);
			}
	for(reg int i=1;i<=cntS;++i)
		for(reg int j=i+1;j<=cntS;++j)
			if(check(S[i],S[j])){
				reg int a=S[i].id,b=S[j].id;
				Add_Tube(a+n,b,INF);
				Add_Tube(b+n,a,INF);
			}
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=cntR;++i){
		if(checkS(R[i]))
			Add_Tube(s,R[i].id,INF);
		if(checkT(R[i]))
			Add_Tube(R[i].id+n,t,INF);
	}
	for(reg int i=1;i<=cntS;++i){
		if(checkS(S[i]))
			Add_Tube(s,S[i].id,INF);
		if(checkT(S[i]))
			Add_Tube(S[i].id+n,t,INF);
	}
	reg int ans=Dinic(s,t);
	printf("%d\n",ans);
	return 0;
}