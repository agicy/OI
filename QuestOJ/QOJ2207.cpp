#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=180+5;
const int MAXM=40000+5;
const int MAXSIZE=180+5;

int n,m;

struct Matrix{
	bitset<MAXSIZE> unit[MAXSIZE];
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		for(reg int k=1;k<=n;++k)
			for(reg int i=1;i<=n;++i)
				if(unit[i][k])
					res.unit[i]|=(a.unit[k]);
		return res;
	}
};

struct Edge{
	int u,v,lv;
	inline void Read(void){
		u=read(),v=read(),lv=read();
		return;
	}
	inline bool operator<(const Edge& a)const{
		return lv<a.lv;
	}
};

Edge E[MAXM];

inline void pow(Matrix x,reg int exp,Matrix& res){
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return;
}

int c,W[MAXM];
ll f[MAXN][MAXN];

struct Node{
	int id;
	ll dis;
	inline Node(reg int id=0,reg ll dis=0):id(id),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXN];
ll dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int main(void){
	n=read(),m=read(),c=read();
	for(reg int i=1;i<=m;++i)
		E[i].Read();
	for(reg int i=1;i<=c;++i)
		W[i]=read();
	for(reg int i=1;i<=m;++i)
		E[i].lv=W[E[i].lv];
	sort(E+1,E+m+1);
	ll ans=INF;
	Matrix t;
	for(reg int i=1;i<=n;++i)
		t.unit[i][i]=true;
	for(reg int i=1;i<=m;++i){
		Matrix G;
		for(reg int j=1;j<i;++j)
			G.unit[E[j].u][E[j].v]=true;
		reg int exp=E[i].lv-E[i-1].lv;
		pow(G,exp,t);
		
		Add_Edge(E[i].u,E[i].v,1);
		
		memset(vis,false,sizeof(vis));
		memset(dis,0X3F,sizeof(dis));
		for(reg int j=1;j<=n;++j)
			if(t.unit[1][j]){
				Q.push(Node(j,0));
				dis[j]=0;
			}
		while(!Q.empty()){
			reg int ID=Q.top().id;
			Q.pop();
			if(vis[ID])
				continue;
			vis[ID]=true;
			for(reg int i=head[ID];i;i=Next[i])
				if(dis[to[i]]>dis[ID]+w[i]){
					dis[to[i]]=dis[ID]+w[i];
					Q.push(to[i]);
				}
		}
		ans=min(ans,E[i].lv+dis[n]);
	}
	if(ans!=INF)
		printf("%lld\n",ans);
	else
		puts("Impossible");
	return 0;
}