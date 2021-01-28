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

const int MAXN=1e5+5;

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

inline ll dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

inline ll getLen(const Vector& a){
	return a.x*a.x+a.y*a.y;
}

int n,m,q;
vector<Point> a,b;
vector<Vector> ea,eb;
Point base;
vector<Vector> p;

inline bool cmpx(const Point& a,const Point& b){
	reg ll s=cross(a-base,b-base);
	if(s)
		return s>0;
	else
		return getLen(a-base)<getLen(b-base);
}

inline bool check(const Point& x){
	Vector vec=x-p.front();
	if(cross(vec,p.back()-p.front())<0||cross(vec,*(p.begin()+1)-p.front())>0)
		return 0;
	reg int pos=lower_bound(p.begin()+1,p.end(),x,cmpx)-(p.begin()+1);
	return cross(x-p[pos],p[(pos+1)%p.size()]-p[pos])<=0;
}

inline bool cmp(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

inline vector<Point> getCon(vector<Point> p){
	sort(p.begin(),p.end(),cmp);
	reg int top=0;
	static Point S[MAXN];
	reg int n=p.size();
	for(reg int i=0;i<n;++i){
		while(top>1&&cross(S[top]-S[top-1],p[i]-S[top-1])<=0)
			--top;
		S[++top]=p[i];
	}
	reg int tmp=top;
	for(reg int i=n-2;i>=0;--i){
		while(top>tmp&&cross(S[top]-S[top-1],p[i]-S[top-1])<=0)
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

int main(void){
	n=read(),m=read(),q=read();
	a.resize(n),b.resize(m);
	for(reg int i=0;i<n;++i)
		a[i].x=read(),a[i].y=read();
	for(reg int i=0;i<m;++i)
		b[i].x=-read(),b[i].y=-read();
	a=getCon(a),b=getCon(b);
	n=a.size(),m=b.size();
	ea.resize(n),eb.resize(m);
	for(reg int i=0;i<n;++i)
		ea[i]=a[(i+1)%n]-a[i];
	for(reg int i=0;i<m;++i)
		eb[i]=b[(i+1)%m]-b[i];
	p.push_back(a[0]+b[0]);
	reg int l=0,r=0;
	while(l<n&&r<m)
		p.push_back(p.back()+(cross(ea[l],eb[r])>=0?ea[l++]:eb[r++]));
	while(l<n)
		p.push_back(p.back()+ea[l++]);
	while(r<m)
		p.push_back(p.back()+eb[r++]);
	while(p.size()>=2&&cross(p.back()-*(p.end()-2),p.front()-*(p.end()-2))<=0)
		p.pop_back();
	base=p.front();
	for(reg int i=1;i<=q;++i){
		static Point delta;
		delta.x=read(),delta.y=read();
		printf("%d\n",check(delta));
	}
	return 0;
}