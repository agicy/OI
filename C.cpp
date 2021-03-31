#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const double eps=1e-6;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

inline double sqr(reg double x){
	return x*x;
}

namespace geometry{
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
		inline Vector operator/(reg double a)const{
			return Vector(x/a,y/a);
		}
		inline double len(void)const{
			return sqrt(sqr(x)+sqr(y));
		}
	};
	inline double dot(const Vector& a,const Vector& b){
		return a.x*b.x+a.y*b.y;
	}
	inline double cross(const Vector& a,const Vector& b){
		return a.x*b.y-a.y*b.x;
	}
	typedef Vector Point;
	inline bool cmp(const Point& a,const Point& b){
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	}
	typedef vector<Point> poly;
	inline poly getCon(poly p){
		sort(p.begin(),p.end(),cmp);
		reg int top=0;
		const int MAXN=5e5+5;
		static Point S[MAXN];
		reg int n=p.size();
		for(reg int i=0;i<n;++i){
			while(top>1&&sgn(cross(S[top]-S[top-1],p[i]-S[top-1]))<=0)
				--top;
			S[++top]=p[i];
		}
		reg int tmp=top;
		for(reg int i=n-2;i>=0;--i){
			while(top>tmp&&sgn(cross(S[top]-S[top-1],p[i]-S[top-1]))<=0)
				--top;
			S[++top]=p[i];
		}
		if(n>1)
			--top;
		p.resize(top);
		for(reg int i=0;i<top;++i)
			p[i]=S[i+1];
		return p;
	}
}

using namespace geometry;

int n;

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		poly a;
		a.resize(n);
		for(reg int i=0;i<n;++i)
			a[i].x=read(),a[i].y=read();
		poly res=getCon(a);
		reg int m=read();
		for(reg int i=1;i<=m;++i){
			static int x,y,r;
			x=read(),y=read(),r=read();
			Point cir(x,y);
			reg bool flag=true;
			if(res.size()<=2)
				flag=false;
			for(reg int j=0,siz=res.size();j<siz&&flag;++j){
				Point a=res[j],b=res[(j+1)%siz];
				reg double S=cross(a-cir,b-cir);
				if(sgn(S/(a-b).len()-r)<0)
					flag=false;
			}
			putchar('0'|flag);
		}
		putchar('\n');
	}
	flush();
	return 0;
}