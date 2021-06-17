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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=300+5;
const int MAXX=300+5;

struct Node{
	int x,y;
};

int n;
Node a[MAXN];

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

inline int cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

inline bool cmp(const Vector& a,const Vector& b){
	return cross(a,b)<0;
}

const ll inf=0x3f3f3f3f3f3f3f3f;
Vector V[MAXN];
int prex[MAXN];
int sum[MAXN];
ll f[MAXN][MAXN*MAXX];

bool ed;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read();
	for(reg int i=1;i<=n;++i)
		V[i]=Vector(max(a[i].x,a[i].y),min(a[i].x,a[i].y));
	sort(V+1,V+n+1,cmp);
	for(reg int i=1;i<=n;++i){
		sum[i]=sum[i-1]+(V[i].x+V[i].y);
		prex[i]=prex[i-1]+V[i].x;
	}
	for(reg int i=0;i<=n;++i)
		for(reg int j=0;j<=prex[i];++j)
			f[i][j]=-inf;
	f[0][0]=0;
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<=prex[i];++j)
			if(f[i][j]>=0){
				f[i+1][j+V[i+1].y]=max(f[i+1][j+V[i+1].y],f[i][j]+2ll*V[i+1].x*j);
				f[i+1][j+V[i+1].x]=max(f[i+1][j+V[i+1].x],f[i][j]+2ll*(sum[i]-j)*V[i+1].x);
			}
	reg ll ans=0;
	for(reg int i=0;i<=prex[n];++i)
		ans=max(ans,f[n][i]);
	for(reg int i=1;i<=n;++i)
		ans+=a[i].x*a[i].y;
	printf("%.2lf\n",ans*0.5);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}