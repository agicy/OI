#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

inline ll sqr(reg ll x){
	return x*x;
}

const int MAXN=250+5;
const int MAXM=250+5;
const int MAXV=MAXN*MAXM;
const int inf=0x3f3f3f3f;

struct point{
	int x,y;
	inline point(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

struct plain{
	int r,c;
	inline plain(reg int r=0,reg int c=0):r(r),c(c){
		return;
	}
	inline bool operator<(const plain& a)const{
		return r<a.r;
	}
};

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

int n,m,W;
int id[MAXN][MAXM];
point pos[MAXN];
plain pie[MAXM],S[MAXM];
vector<Edge> G[MAXV];

inline void Add_Edge(reg int u,reg int v,reg int len){
	G[u].push_back(Edge(v,len));
	return;
}

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

bool vis[MAXV];
int dis[MAXV];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline int dijkstra(reg int s,reg int t){
	memset(vis,false,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	while(!Q.empty())Q.pop();
	dis[s]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		reg int u=Q.top().id;
		Q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		if(u==t)
			return dis[t];
		for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
			reg int v=it->v,w=it->w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return dis[t];
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),m=read(),W=read();
		for(reg int i=1;i<=n;++i)
			pos[i].x=read(),pos[i].y=read();
		for(reg int i=1;i<=m;++i)
			pie[i].r=read(),pie[i].c=read();
		sort(pie+1,pie+m+1);
		reg int top=0;
		for(reg int i=1;i<=m;++i){
			while(top&&S[top].c>=pie[i].c)
				--top;
			S[++top]=pie[i];
		}
		m=top;
		reg int s=0,t=n*m+1,tot=0;
		for(reg int i=s;i<=t;++i)
			G[i].clear();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j){
				id[i][j]=++tot;
				if(pos[i].y<=S[j].r)
					Add_Edge(s,tot,S[j].c);
				if(pos[i].y+S[j].r>=W)
					Add_Edge(tot,t,0);
			}
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<m;++j)
				Add_Edge(id[i][j],id[i][j+1],S[j+1].c-S[j].c);
		for(reg int i=1;i<=n;++i)
			for(reg int j=i+1;j<=n;++j){
				reg int ptr=1;
				reg ll dis=sqr(pos[i].x-pos[j].x)+sqr(pos[i].y-pos[j].y);
				for(reg int k=m;k>=1;--k){
					while(ptr<=m&&sqr(S[k].r+S[ptr].r)<dis)
						++ptr;
					if(ptr<=m){
						Add_Edge(id[i][k],id[j][ptr],S[ptr].c);
						Add_Edge(id[j][k],id[i][ptr],S[ptr].c);
					}
				}
			}
		reg int ans=dijkstra(s,t);
		if(ans==inf)
			puts("impossible");
		else
			printf("%d\n",ans);
	}
	return 0;
}