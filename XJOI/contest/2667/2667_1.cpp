#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e3+5;
const ll inf=1e18;
const double eps=1e-6;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

struct Vector{
	ll x,y;
	inline Vector(reg ll x=0,reg ll y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline double cross(const Vector& a,const Vector& b){
	return 1.0*a.x*b.y-1.0*a.y*b.x;
}

typedef Vector Point;

int n;
int x[MAXN],y[MAXN];
int sumx[MAXN],sumy[MAXN];
ll f[MAXN][MAXN];
int headr[MAXN],tailr[MAXN];
Point row[MAXN][MAXN];
int headc[MAXN],tailc[MAXN];
Point col[MAXN][MAXN];

inline Point getPointR(reg int i,reg int j){
	return Point(2*sumy[j],1ll*sumy[j]*sumy[j]-f[i][j]);
}

inline ll getValR(const Point& p,reg int i,reg int j){
	return -((p.y-p.x*sumy[j-1])-x[i]*y[j]+1ll*sumy[j-1]*sumy[j-1]);
}

inline Point getPointC(reg int i,reg int j){
	return Point(2*sumx[i],1ll*sumx[i]*sumx[i]-f[i][j]);
}

inline ll getValC(const Point& p,reg int i,reg int j){
	return -((p.y-p.x*sumx[i-1])-x[i]*y[j]+1ll*sumx[i-1]*sumx[i-1]);
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			x[i]=read();
		x[n+1]=0;
		for(reg int i=1;i<=n;++i)
			y[i]=read();
		y[n+1]=0;
		for(reg int i=1;i<=n+1;++i)
			sumx[i]=sumx[i-1]+x[i],sumy[i]=sumy[i-1]+y[i];
		for(reg int i=0;i<=n;++i)
			headr[i]=tailr[i]=0,headc[i]=tailc[i]=0;
		for(reg int i=0;i<=n+1;++i)
			for(reg int j=0;j<=n+1;++j)
				f[i][j]=-inf;
		f[0][0]=0;
		for(reg int i=1;i<=n+1;++i){
			for(reg int j=1;j<=n+1;++j){
				reg int __l,__r,__mid,ptr;
				Point r=getPointR(i-1,j-1);
				while(tailr[i-1]-headr[i-1]>1&&sgn(cross(row[i-1][tailr[i-1]-1]-row[i-1][tailr[i-1]-2],r-row[i-1][tailr[i-1]-2]))<=0)
					--tailr[i-1];
				row[i-1][tailr[i-1]++]=r;
				__l=headr[i-1],__r=tailr[i-1]-1;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(sgn(row[i-1][__mid+1].y-row[i-1][__mid].y-1.0*sumy[j-1]*(row[i-1][__mid+1].x-row[i-1][__mid].x))>=0)
						__r=__mid;
					else
						__l=__mid+1;
				}
				ptr=__l;
				f[i][j]=max(f[i][j],getValR(row[i-1][ptr],i,j));

				Point c=getPointC(i-1,j-1);
				while(tailc[j-1]-headc[j-1]>1&&sgn(cross(col[j-1][tailc[j-1]-1]-col[j-1][tailc[j-1]-2],c-col[j-1][tailc[j-1]-2]))<=0)
					--tailc[j-1];
				col[j-1][tailc[j-1]++]=c;
				__l=headc[j-1],__r=tailc[j-1]-1;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(sgn(col[j-1][__mid+1].y-col[j-1][__mid].y-1.0*sumx[i-1]*(col[j-1][__mid+1].x-col[j-1][__mid].x))>=0)
						__r=__mid;
					else
						__l=__mid+1;
				}
				ptr=__l;
				f[i][j]=max(f[i][j],getValC(col[j-1][ptr],i,j));

				//printf("i=%d j=%d f=%lld\n",i,j,f[i][j]);
			}
		}
		printf("%lld\n",f[n+1][n+1]);
		fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	}
	return 0;
}