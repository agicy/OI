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

const int MAXN=100+5;
const int MAXM=20+5;
const int MAXD=MAXN*MAXM;
const int MAXE=MAXM*(MAXM-1)/2;

int n,m,k,e,d;
int p[MAXD],a[MAXD],b[MAXD];
int cnt,head[MAXM],to[MAXE<<1],Next[MAXE<<1];
ll w[MAXE<<1];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id;
	ll val;
	inline Node(reg int id=0,reg ll val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

bool del[MAXM];
bool vis[MAXM];
ll dis[MAXM];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	fill(dis+1,dis+m+1,1e15);
	dis[s]=0,Q.push(Node(s,dis[s]));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]&&!del[v]){
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

ll ans[MAXN][MAXN],f[MAXN];

int main(void){
	n=read(),m=read(),k=read(),e=read();
	for(reg int i=0;i<e;++i){
		static int x,y,c;
		x=read(),y=read(),c=read();
		Add_Edge(x,y,c),Add_Edge(y,x,c);
	}
	d=read();
	for(reg int i=1;i<=d;++i)
		p[i]=read(),a[i]=read(),b[i]=read();
	memset(ans,0,sizeof(ans));
	for(reg int len=1;len<=n;++len)
		for(reg int l=1;l+len-1<=n;++l){
			reg int r=l+len-1;
			memset(del,false,sizeof(del));
			for(reg int j=1;j<=d;++j)
				for(reg int k=l;k<=r;++k)
					if(a[j]<=k&&k<=b[j]){
						del[p[j]]=true;
						break;
					}
			dijkstra(1);
			ans[l][r]+=dis[m];
		}
	f[0]=0,f[1]=ans[1][1];
	for(reg int i=2;i<=n;++i){
		f[i]=ans[1][i]*i;
		for(reg int j=i-1;j>=0;--j)
			f[i]=min(f[i],f[j]+ans[j+1][i]*(i-j)+k);
	}
	printf("%lld\n",f[n]);
	return 0;
}