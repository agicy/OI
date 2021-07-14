#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=300+5;
const int inf=0x3f3f3f3f;

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

namespace Network{
	const int MAXV=2*MAXN;
	const int MAXE=2*(MAXN*MAXN*2+2*MAXN+MAXN);
	int cnt,head[MAXV],to[MAXE],w[MAXE],nxt[MAXE];
	inline void init(reg int s,reg int t){
		cnt=1,memset(head+s,0,sizeof(int)*(t-s+1));
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg int lim){
		nxt[++cnt]=head[u];
		to[cnt]=v,w[cnt]=lim;
		head[u]=cnt;
		return;
	}
	inline int Add_Tube(reg int u,reg int v,reg int lim){
		Add_Edge(u,v,lim),Add_Edge(v,u,0);
		return cnt;
	}
	int dep[MAXV];
	int cur[MAXV];
	inline bool bfs(reg int s,reg int t){
		memset(dep,-1,sizeof(dep));
		reg int _head=0,_tail=0;
		static int Q[MAXV];
		dep[s]=1,Q[_tail++]=s;
		while(_head<_tail){
			reg int u=Q[_head++];
			cur[u]=head[u];
			for(reg int i=head[u];i;i=nxt[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]>0)
					dep[v]=dep[u]+1,Q[_tail++]=v;
			}
		}
		return dep[t]!=-1;
	}
	inline int dfs(reg int u,reg int t,reg int lim){
		if(u==t)
			return lim;
		reg int flow=0;
		for(reg int& i=cur[u];i;i=nxt[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+1&&w[i]>0){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f,w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		return flow;
	}
	inline int dinic(reg int s,reg int t){
		reg int res=0;
		while(bfs(s,t))
			res+=dfs(s,t,inf);
		return res;
	}
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
	return check(a,Square{0,0,cy,cx,cy});
}

inline bool checkT(const Round& a){
	return check(a,Square{0,0,0,cx,0});
}

inline bool checkS(const Square& a){
	return check(a,Square{0,0,cy,cx,cy});
}

inline bool checkT(const Square& a){
	return check(a,Square{0,0,0,cx,0});
}

int n;
int id[MAXN];

int main(void){
	cx=read(),cy=read(),n=read();
	reg int cntR=0,cntS=0;
	for(reg int i=1;i<=n;++i)
		switch(read()){
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
	reg int s=0,t=2*n+1;
	Network::init(s,t);
	for(reg int i=1;i<=n;++i)
		id[i]=Network::Add_Tube(i,i+n,1)-1;
	for(reg int i=1;i<=cntR;++i)
		for(reg int j=1;j<=cntS;++j)
			if(check(R[i],S[j])){
				reg int a=R[i].id,b=S[j].id;
				Network::Add_Tube(a+n,b,inf);
				Network::Add_Tube(b+n,a,inf);
			}
	for(reg int i=1;i<=cntR;++i)
		for(reg int j=i+1;j<=cntR;++j)
			if(check(R[i],R[j])){
				reg int a=R[i].id,b=R[j].id;
				Network::Add_Tube(a+n,b,inf);
				Network::Add_Tube(b+n,a,inf);
			}
	for(reg int i=1;i<=cntS;++i)
		for(reg int j=i+1;j<=cntS;++j)
			if(check(S[i],S[j])){
				reg int a=S[i].id,b=S[j].id;
				Network::Add_Tube(a+n,b,inf);
				Network::Add_Tube(b+n,a,inf);
			}
	for(reg int i=1;i<=cntR;++i){
		if(checkS(R[i]))
			Network::Add_Tube(s,R[i].id,inf);
		if(checkT(R[i]))
			Network::Add_Tube(R[i].id+n,t,inf);
	}
	for(reg int i=1;i<=cntS;++i){
		if(checkS(S[i]))
			Network::Add_Tube(s,S[i].id,inf);
		if(checkT(S[i]))
			Network::Add_Tube(S[i].id+n,t,inf);
	}
	reg int ans1=Network::dinic(s,t);
	reg int tot=0;
	static int ans2[MAXN];
	for(reg int i=1;i<=n;++i)
		if(!(Network::w[id[i]]||Network::bfs(i,i+n))){
			ans2[++tot]=i;
			Network::dinic(i,s),Network::dinic(t,i+n);
			Network::w[id[i]]=Network::w[id[i]^1]=0;
		}
	printf("%d\n",ans1);
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",ans2[i],i==tot?'\n':' ');
	return 0;
}