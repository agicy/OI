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

const double eps=1e-8;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

struct Vector{
	double x,y;
	inline Vector(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline double dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline double cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;
typedef vector<Point> poly;

inline bool cmp(const Point& a,const Point& b){
	return a.x<b.x||(sgn(a.x-b.x)==0&&a.y<b.y);
}

inline poly Andrew(poly p){
	reg int n=p.size();
	sort(p.begin(),p.end(),cmp);
	poly res;
	res.clear();
	for(reg int i=0;i<n;++i){
		while(res.size()>1&&sgn(cross(res.back()-*(res.end()-2),p[i]-*(res.end()-2)))<0)
			res.pop_back();
		res.push_back(p[i]);
	}
	reg unsigned tmp=res.size();
	for(reg int i=n-2;i>=0;--i){
		while(res.size()>tmp&&sgn(cross(res.back()-*(res.end()-2),p[i]-*(res.end()-2)))<0)
			res.pop_back();
		res.push_back(p[i]);
	}
	if(n>1)
		res.pop_back();
	return res;
}

int n;
poly p,ans;

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		p.resize(n);
		for(reg int i=0;i<n;++i)
			p[i].x=read(),p[i].y=read();
		ans=Andrew(p);
		printf("%lu\n",ans.size());
		for(reg unsigned i=0;i<ans.size();++i)
			printf("%.0lf %.0lf\n",ans[i].x,ans[i].y);
	}
	return 0;
}