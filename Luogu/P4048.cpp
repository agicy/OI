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

const int MAXN=200+5;
const int MAXM=200+5;
const int MAXK=200+5;
const int MAXV=2*MAXN;
const int MAXE=(MAXN+MAXM+MAXN*MAXM)*2;

inline int sqr(reg int x){
	return x*x;
}

struct Witch{
	int x,y,r,t;
	inline void Read(void){
		x=read(),y=read(),r=read(),t=read();
		return;
	}
};

struct Spirit{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
};

struct Tree{
	int x,y,r;
	inline void Read(void){
		x=read(),y=read(),r=read();
		return;
	}
};

int n,m,K,s,t;
Witch W[MAXN];
Spirit S[MAXM];
Tree T[MAXK];

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
int cnt_b,head_b[MAXV],w_b[MAXE];

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

inline bool check(reg int mid){
	cnt=cnt_b;
	memcpy(head,head_b,sizeof(head_b));
	memcpy(w,w_b,sizeof(w_b));
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,mid/W[i].t+1);
	reg int flow=Dinic(s,t);
	return flow>=m;
}

inline bool check(const Witch& W,const Spirit& S,const Tree& T){
	reg ll dx=S.x-W.x,dy=S.y-W.y;
	reg ll a=dy,b=-dx,c=W.y*dx-W.x*dy;
	reg ll up=abs(a*T.x+b*T.y+c);
	reg bool f1=up*up>1ll*sqr(T.r)*(a*a+b*b);
	if(f1)
		return f1;
	else
		if((W.x-T.x)*(S.x-T.x)<0)
			return false;
		else
			return (sqr(W.x-T.x)+sqr(W.y-T.y)>sqr(T.r))&&(sqr(S.x-T.x)+sqr(S.y-T.y)>sqr(T.r));
}

int main(void){
	n=read(),m=read(),K=read();
	s=0,t=n+m+1;
	int Maxt=0;
	for(reg int i=1;i<=n;++i){
		W[i].Read();
		Maxt=max(Maxt,W[i].t);
	}
	for(reg int i=1;i<=m;++i)
		S[i].Read();
	for(reg int i=1;i<=K;++i)
		T[i].Read();
	for(reg int i=1;i<=m;++i)
		Add_Tube(i+n,t,1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(sqr(W[i].x-S[j].x)+sqr(W[i].y-S[j].y)<=sqr(W[i].r)){
				reg bool flag=true;
				for(reg int k=1;k<=K;++k)
					if(!check(W[i],S[j],T[k])){
						flag=false;
						break;
					}
				if(flag)
					Add_Tube(i,j+n,1);
			}
	cnt_b=cnt;
	memcpy(head_b,head,sizeof(head));
	memcpy(w_b,w,sizeof(w));
	reg int l=0,r=m*Maxt,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	if(l>m*Maxt)
		puts("-1");
	else
		printf("%d\n",l);
	return 0;
}
