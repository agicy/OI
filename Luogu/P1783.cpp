#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int MAXM=800+5;
const double eps=1e-5;

struct Node{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
};

int n,m;
Node a[MAXM];
double dis[MAXM][MAXM];
bool vis[MAXM];
queue<int> Q;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

inline bool check(reg double mid){
	memset(vis,false,sizeof(vis));
	while(!Q.empty())Q.pop();
	for(int i=1;i<=m;++i)
		if(sgn(a[i].x-mid)<=0)
			Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		if(sgn(a[u].x+mid-n)>=0)
			return true;
		for(int i=1;i<=m;++i)
			if(!vis[i]&&sgn(dis[u][i]-2*mid)<=0)
				Q.push(i);
	}
	return false;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		a[i].Read();
	for(reg int i=1;i<=m;++i)
		for(reg int j=i+1;j<=m;++j)
			dis[i][j]=dis[j][i]=getDis(a[i],a[j]);
	reg double l=0,r=2e3,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%.2lf\n",0.5*(l+r));
	return 0;
}