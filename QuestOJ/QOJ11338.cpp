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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1.5e3+5;

struct Vector{
	int x,y;
	inline ll getLen(void)const{
		return 1ll*x*x+1ll*y*y;
	}
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

inline ll dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

struct Data{
	Vector len;
	pair<int,int> mid;
	inline Data(void){
		return;
	}
	inline Data(const Vector& len,const pair<int,int>& mid):len(len),mid(mid){
		return;
	}
	inline bool operator<(const Data& a)const{
		return len.getLen()<a.len.getLen()||(len.getLen()==a.len.getLen()&&mid<a.mid);
	}
};

int n;
Vector p[MAXN];
Data d[MAXN*MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i].x=read(),p[i].y=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			d[++tot]=Data(p[j]-p[i],make_pair(p[i].x+p[j].x,p[i].y+p[j].y));
	sort(d+1,d+tot+1);
	reg ll ans=0;
	for(reg int l=1,r;l<=tot;l=r+1){
		r=l;
		while(r<tot&&d[r+1].len.getLen()==d[l].len.getLen()&&d[r+1].mid==d[l].mid)
			++r;
		for(reg int i=l;i<=r;++i)
			for(reg int j=i+1;j<=r;++j)
				ans=max(ans,abs(cross(d[i].len,d[j].len))>>1);
	}
	printf("%lld\n",ans);
	return 0;
}