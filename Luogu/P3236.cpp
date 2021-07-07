#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline int dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline int cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

const int MAXN=70+5;
const int inf=0x3f3f3f3f;

namespace KM{
	int G[MAXN][MAXN];
	int mat[MAXN];
	int slack[MAXN],ex[MAXN],ey[MAXN];
	int pre[MAXN];
	int tim,vis[MAXN];
	inline void bfs(reg int n,reg int u){
		fill(pre+1,pre+n+1,0);
		for(reg int i=1;i<=n;++i)
			slack[i]=inf;
		reg int x,y=0;
		mat[y]=u;
		while(true){
			x=mat[y],vis[y]=tim;
			reg int tmp=0;
			reg int delta=inf;
			for(reg int i=1;i<=n;++i){
				if(vis[i]==tim)
					continue;
				if(slack[i]>ex[x]+ey[i]-G[x][i]){
					slack[i]=ex[x]+ey[i]-G[x][i];
					pre[i]=y;
				}
				if(slack[i]<delta){
					delta=slack[i];
					tmp=i;
				}
			}
			for(reg int i=0;i<=n;++i)
				if(vis[i]==tim)
					ex[mat[i]]-=delta,ey[i]+=delta;
				else
					slack[i]-=delta;
			y=tmp;
			if(!mat[y])
				break;
		}
		while(y){
			mat[y]=mat[pre[y]];
			y=pre[y];
		}
		return;
	}
	inline int KM(reg int n){
		fill(mat+1,mat+n+1,0);
		fill(ex+1,ex+n+1,0);
		fill(ey+1,ey+n+1,0);
		for(reg int i=1;i<=n;++i)
			++tim,bfs(n,i);
		reg int res=0;
		for(reg int i=1;i<=n;++i)
			if(mat[i])
				res+=G[mat[i]][i];
		return res;
	}
}

int n;
int a[MAXN][MAXN],b[MAXN][MAXN];
int w[MAXN][MAXN];
int ans;

inline Point getVal(void){
	Point res(0,0);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			KM::G[i][j]=-w[i][j];
	KM::KM(n);
	for(reg int i=1;i<=n;++i)
		res=res+Point(a[KM::mat[i]][i],b[KM::mat[i]][i]);
	ans=min(ans,res.x*res.y);
	return res;
}

inline void solve(const Point& A,const Point& B){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			w[i][j]=(A.y-B.y)*a[i][j]+(B.x-A.x)*b[i][j];
	Point C=getVal();
	if(cross(B-A,C-A)<0)
		solve(A,C),solve(C,B);
	return;
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				a[i][j]=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				b[i][j]=read();
		ans=inf;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				w[i][j]=a[i][j];
		Point A=getVal();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				w[i][j]=b[i][j];
		Point B=getVal();
		solve(A,B);
		printf("%d\n",ans);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}