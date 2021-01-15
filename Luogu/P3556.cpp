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

const int MAXN=5e3+5;
const int MAXM=5e3+5;
const int MAXK=1e6+5;

int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Node{
	int id,p;
	inline Node(reg int id=0,reg int p=0):id(id),p(p){
		return;
	}
};

bool vis[MAXN][2];
int dis[MAXN][2];
queue<Node> Q;

inline void bfs(reg int s){
	memset(vis,false,sizeof(vis));
	vis[s][0]=true,dis[s][0]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg int u=s.id,p=s.p;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[v][p^1]){
				vis[v][p^1]=true;
				dis[v][p^1]=dis[u][p]+1;
				Q.push(Node(v,p^1));
			}
		}
	}
	return;
}

struct querys{
	int id,t,d;
	inline querys(reg int id=0,reg int t=0,reg int d=0):id(id),t(t),d(d){
		return;
	}
};

int n,m,k;
vector<querys> q[MAXN];
bool ans[MAXK];

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	for(reg int i=1;i<=k;++i){
		static int s,t,d;
		s=read(),t=read(),d=read();
		q[s].push_back(querys(i,t,d));
	}
	for(reg int i=1;i<=n;++i)
		if(q[i].size()){
			bfs(i);
			for(reg int j=0,siz=q[i].size();j<siz;++j){
				reg int v=q[i][j].t,d=q[i][j].d;
				if(v==i)
					ans[q[i][j].id]=(head[i]&&vis[i][d&1]&&dis[i][d&1]<=d)||(!head[i]&&d==0);
				else
					ans[q[i][j].id]=(vis[v][d&1]&&dis[v][d&1]<=d);
			}
		}
	for(reg int i=1;i<=k;++i)
		puts(ans[i]?"TAK":"NIE");
	return 0;
}