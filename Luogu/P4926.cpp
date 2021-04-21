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
const int inf=0x3f3f3f3f;
const double eps=1e-5;

int n,s,t;

struct Edge{
	int v;
	double w;
	inline Edge(reg int v=0,reg double w=0):v(v),w(w){
		return;
	}
};

vector<Edge> G[MAXN][3];
bool inque[MAXN];
int in[MAXN];
double dis[MAXN];

inline bool spfa(reg double mid){
	queue<int> Q;
	fill(inque,inque+n+1,false),fill(in,in+n+1,0),fill(dis,dis+n+1,-inf);
	inque[n+1]=true,in[n+1]=1,dis[n+1]=0,Q.push(n+1);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=0;i<3;++i)
			for(Edge e:G[u][i]){
				reg double w;
				switch(i){
					case 0: w=e.w;break;
					case 1: w=log2(e.w-mid);break;
					case 2: w=-log2(e.w+mid);break;
				}
				if(dis[e.v]<dis[u]+w){
					dis[e.v]=dis[u]+w;
					if(!inque[e.v]){
						inque[e.v]=true;
						if(++in[e.v]>=n+1)
							return false;
						Q.push(e.v);
					}
				}
			}
	}
	return true;
}

int main(void){
	n=read(),s=read(),t=read();
	for(reg int i=1;i<=s;++i){
		static int o,a,b;
		static double k;
		o=read(),a=read(),b=read(),k=read();
		G[b][o].push_back(Edge(a,k));
	}
	for(reg int i=1;i<=t;++i){
		static int c;
		static double x;
		c=read(),x=read();
		G[0][0].push_back(Edge(c,log2(x)));
		G[c][0].push_back(Edge(0,-log2(x)));
	}
	for(reg int i=0;i<=n;++i)
		G[n+1][0].push_back(Edge(i,0));
	if(spfa(0))
		puts("-1");
	else{
		reg double l=0,r=10,mid;
		while(r-l>eps){
			mid=0.5*(l+r);
			if(spfa(mid))
				r=mid;
			else
				l=mid;
		}
		printf("%.10lf\n",l);
	}
	return 0;
}