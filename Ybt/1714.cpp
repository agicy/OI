#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=35+5;
const int MAXM=2.5e4+5;
const int MAXQ=2e5+5;
const double inf=1e40;

struct Node{
	int u,v;
	inline Node(reg int u=0,reg int v=0):u(u),v(v){
		return;
	}
	inline bool operator<(const Node& a)const{
		return u<a.u;
	}
};

struct querys{
	int id;
	double k1,k2;
	inline querys(reg int id=0,reg double k1=0.0,reg double k2=0.0):id(id),k1(k1),k2(k2){
		return;
	}
	inline bool operator<(const querys& a)const{
		return k1*a.k2>k2*a.k1;
	}
};

int n,m,Q;
vector<Node> p[MAXN][MAXN];
int head[MAXN][MAXN],siz[MAXN][MAXN];
vector<Node> con[MAXN][MAXN];
querys q[MAXQ];
double ans[MAXQ];
bool vis[MAXN];
double dis[MAXN],g[MAXN][MAXN];

inline double prim(reg double k1,reg double k2){
	memset(vis,false,sizeof(vis));
	for(reg int i=1;i<=n;++i){
		dis[i]=inf;
		for(reg int j=i+1;j<=n;++j){
			g[i][j]=g[j][i]=inf;
			if(head[i][j]<siz[i][j]){
				int s=siz[i][j];
				while(head[i][j]<s-1&&1.0*(con[i][j][head[i][j]+1].v-con[i][j][head[i][j]].v)/(con[i][j][head[i][j]+1].u-con[i][j][head[i][j]].u)<-k1/k2)
					++head[i][j];
				g[i][j]=g[j][i]=k1*con[i][j][head[i][j]].u+k2*con[i][j][head[i][j]].v;
			}
		}
	}
	reg double sum=0;
	dis[1]=0;
	for(reg int i=1;i<=n;++i){
		reg int pos=0;
		reg double Min=inf;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&dis[j]<Min)
				Min=dis[j],pos=j;
		vis[pos]=true;
		sum+=dis[pos];
		for(reg int j=1;j<=n;++j)
			if(!vis[j])
				dis[j]=min(dis[j],g[pos][j]);
	}
	return sum;
}

int main(void){
	n=read(),m=read(),Q=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,u,v;
		x=read(),y=read(),u=read(),v=read();
		if(x==y)
			continue;
		if(x>y)
			swap(x,y);
		p[x][y].push_back(Node(u,v));
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			if(!p[i][j].empty()){
				sort(p[i][j].begin(),p[i][j].end());
				reg int &s=siz[i][j];
				for(reg int k=0,siz=p[i][j].size();k<siz;++k){
					static Node x;
					x=p[i][j][k];
					if(s>0&&con[i][j][s-1].u==x.u){
						if(con[i][j][s-1].v<x.v)
							continue;
						else
							con[i][j].pop_back(),--s;
					}
					while(s>1&&1ll*(con[i][j][s-2].v-con[i][j][s-1].v)*(con[i][j][s-1].u-x.u)>1ll*(con[i][j][s-1].v-x.v)*(con[i][j][s-2].u-con[i][j][s-1].u))
						con[i][j].pop_back(),--s;
					con[i][j].push_back(x),++s;
				}
			}
	for(reg int i=1;i<=Q;++i){
		static double k1,k2;
		scanf("%lf%lf",&k1,&k2);
		q[i]=querys(i,k1,k2);
	}
	sort(q+1,q+Q+1);
	for(reg int i=1;i<=Q;++i)
		ans[q[i].id]=prim(q[i].k1,q[i].k2);
	for(reg int i=1;i<=Q;++i)
		printf("%.3lf\n",ans[i]);
	return 0;
}