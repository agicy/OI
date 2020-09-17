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

const int MAXN=50+5;
const int MAXM=50+5;
const double eps=1e-8;

struct Node{
	double x,y;
};

struct Data{
	int id;
	double t;
	inline Data(reg int id=0,reg double t=0):id(id),t(t){
		return;
	}
};

int n,m,v;
int tot;
double t1,t2;

int mat[MAXN*MAXM];
bool vis[MAXN*MAXM];
vector<int> G[MAXM];

inline bool dfs(reg int u){
	for(reg int i=0,siz=G[u].size();i<siz;++i){
		reg int v=G[u][i];
		if(vis[v])
			continue;
		vis[v]=true;
		if(!mat[v]||dfs(mat[v])){
			mat[v]=u;
			return true;
		}
	}
	return false;
}

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

Node a[MAXM],b[MAXN];
Data T[MAXN*MAXM];

inline bool check(reg double mid){
	memset(mat,0,sizeof(mat));
	for(reg int i=1;i<=m;++i){
		G[i].clear();
		for(int j=1;j<=tot;++j)
			if(T[j].t+getDis(a[i],b[T[j].id])/v<=mid)
				G[i].push_back(j);
	}
	for(reg int i=1;i<=m;++i){
		memset(vis,false,sizeof(vis));
		if(!dfs(i))
			return false;
	}
	return true;
}

int main(void){
	n=read(),m=read(),t1=read()/60.0,t2=read(),v=read();
	tot=n*m;
	for(reg int i=1;i<=m;++i)
		a[i].x=read(),a[i].y=read();
	for(reg int i=1;i<=n;++i)
		b[i].x=read(),b[i].y=read();
	reg int id=0;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			T[++id]=Data(j,(i-1)*(t1+t2)+t1);
	reg double l=t1,r=1e5,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%.6lf\n",r);
	return 0;
}