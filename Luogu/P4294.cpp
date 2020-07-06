#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=10+5;
const int MAXM=10+5;
const int MAXNM=MAXN*MAXM;
const int MAXK=10+1;

int n,m,nm;
bool ans[MAXN][MAXM];
int a[MAXNM];

struct Node{
	int x,y,dis;
	inline Node(reg int x=0,reg int y=0,reg int dis=0):x(x),y(y),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

inline int GetID(reg int x,reg int y){
	return x*m+y;
}

inline bool check(reg int x,reg int y){
	return 0<=x&&x<n&&0<=y&&y<m;
}

bool vis[MAXNM];
int dp[MAXNM][1<<MAXK];
int pre[MAXNM][1<<MAXK][2];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(int S){
	memset(vis,false,sizeof(vis));
	while(!Q.empty()){
		reg int x=Q.top().x,y=Q.top().y;
		int id=GetID(x,y);
		Q.pop();
		vis[GetID(x,y)]=true;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(fx,fy)){
				reg int v=GetID(fx,fy);
				if(dp[v][S]>dp[id][S]+a[v]){
					dp[v][S]=dp[id][S]+a[v];
					pre[v][S][0]=id,pre[v][S][1]=S;
					Q.push(Node(fx,fy,dp[v][S]));
				}
			}
		}
	}
	return;
}

inline void DFS(reg int x,reg int y,reg int S){
	reg int id=GetID(x,y),v=pre[id][S][0],s=pre[id][S][1];
	if(!s)
		return;
	ans[x][y]=true;
	if(v==id)
		DFS(x,y,S^s);
	DFS(v/m,v%m,s);
	return;
}

int main(void){
	n=read(),m=read(),nm=n*m;
	memset(dp,0X3F,sizeof(dp));
	reg int root,k=0;
	for(reg int i=0,tot=0;i<n;++i)
		for(reg int j=0;j<m;++j,++tot){
			a[tot]=read();
			if(!a[tot])
				dp[tot][1<<(k++)]=0,root=tot;
		}
	for(reg int S=1;S<(1<<k);++S){
		for(int i=0;i<nm;++i){
			for(int sub=S&(S-1);sub;sub=S&(sub-1))
				if(dp[i][S]>dp[i][sub]+dp[i][S^sub]-a[i]){
					dp[i][S]=dp[i][sub]+dp[i][S^sub]-a[i];
					pre[i][S][0]=i,pre[i][S][1]=sub;
				}
			if(dp[i][S]!=INF)
				Q.push(Node(i/m,i%m,dp[i][S]));
		}
		Dijkstra(S);
	}
	printf("%d\n",dp[root][(1<<k)-1]);
	DFS(root/m,root%m,(1<<k)-1);
	for(reg int i=0,tot=0;i<n;++i){
		for(reg int j=0;j<m;++j)
			if(!a[tot++])
				putchar('x');
			else
				putchar(ans[i][j]?'o':'_');
		putchar('\n');
	}
	return 0;
}