#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const double eps=1e-6;
const double inf=1e20;

struct Node{
	int x,y,z;
	inline void read(void){
		scanf("%d%d%d",&x,&y,&z);
		return;
	}
};

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

int n;
Node a[MAXN];
bool vis[MAXN];
double len[MAXN][MAXN],cost[MAXN][MAXN];
double f[MAXN];

inline bool check(reg double mid){
	memset(vis,false,sizeof(vis));
	fill(f+1,f+n+1,inf);
	f[1]=0;
	reg double sum=0;
	for(reg int i=1;i<=n;++i){
		reg int pos=0;
		reg double Min=inf;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&f[j]<Min){
				pos=j;
				Min=f[j];
			}
		vis[pos]=true;
		sum+=f[pos];
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&f[j]>cost[pos][j]-mid*len[pos][j])
				f[j]=cost[pos][j]-mid*len[pos][j];
	}
	return sum>=0;
}

int main(void){
	while(scanf("%d",&n)!=EOF&&n!=0){
		for(reg int i=1;i<=n;++i)
			a[i].read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=i+1;j<=n;++j){
				len[i][j]=len[j][i]=getDis(a[i],a[j]);
				cost[i][j]=cost[j][i]=abs(a[i].z-a[j].z);
			}
		reg double l=0,r=1e4,mid;
		while(r-l>eps){
			mid=0.5*(l+r);
			if(check(mid))
				l=mid;
			else
				r=mid;
		}
		printf("%.3lf\n",0.5*(l+r));
	}
	return 0;
}