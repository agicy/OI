#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200+5;
const int MAXV=MAXN;
const int MAXE=MAXN*MAXN*2;

int n;
ll a[MAXN],b[MAXN],c[MAXN];

int cnt[MAXN];

inline void Div(reg int id){
	reg ll x=a[id];
	for(reg ll i=2;i*i<=x;++i)
		if(x%i==0)
			while(x%i==0){
				x/=i;
				++cnt[id];
			}
	if(x!=1)
		++cnt[id];
	return;
}

int Ecnt=1,head[MAXV],to[MAXE],Next[MAXE];
ll w[MAXE],p[MAXE];

inline void Add_Edge(reg int u,reg int v,reg ll len,reg ll val){
	Next[++Ecnt]=head[u];
	to[Ecnt]=v;
	w[Ecnt]=len;
	p[Ecnt]=val;
	head[u]=Ecnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg ll len,reg ll val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXN];
ll dis[MAXN];
queue<int> Q;

inline bool SPFA(int s,reg int t){
	memset(inque,false,sizeof(inque));
	fill(dis+s,dis+t+1,-INF);
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
	return dis[t]>-INF;
}

bool vis[MAXV];
int cur[MAXV];

inline ll DFS(reg int ID,reg int t,reg ll lim){
	if(ID==t)
		return lim;
	vis[ID]=true;
	reg ll flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dis[to[i]]==dis[ID]+p[i]&&w[i]>0&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
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

inline ll Dinic(reg int s,reg int t){
	reg ll res=0,Cost=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		reg ll sum=DFS(s,t,INF);
		if(Cost+sum*dis[t]>=0)
			res+=sum,Cost+=sum*dis[t];
		else
			return res+Cost/(-dis[t]);
	}
	return res;
}

int main(void){
	n=read();
	reg int s=0,t=n+1;
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=n;++i)
		Div(i);
	for(reg int i=1;i<=n;++i)
		if(cnt[i]&1){
			Add_Tube(s,i,b[i],0);
			for(reg int j=1;j<=n;++j)
				if((a[i]%a[j]==0&&cnt[i]==cnt[j]+1)||(a[j]%a[i]==0&&cnt[j]==cnt[i]+1))
					Add_Tube(i,j,INF,c[i]*c[j]);
		}
		else
			Add_Tube(i,t,b[i],0);
	reg ll ans=Dinic(s,t);
	printf("%lld\n",ans);
	return 0;
}