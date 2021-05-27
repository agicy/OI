#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline double sqr(reg double x){
	return x*x;
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

inline bool operator<(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

const int MAXN=100+5;
const double pi=acos(-1.0);

struct Node{
	int id;
	Point p;
	inline bool operator<(const Node& a)const{
		return p<a.p;
	}
};

inline vector<Node> getCon(vector<Node> p){
	sort(p.begin(),p.end());
	reg int top=0;
	static Node S[MAXN];
	reg int n=p.size();
	for(reg int i=0;i<n;++i){
		while(top>1&&cross(S[top].p-S[top-1].p,p[i].p-S[top-1].p)<=0)
			--top;
		S[++top]=p[i];
	}
	reg int tmp=top;
	for(reg int i=n-2;i>=0;--i){
		while(top>tmp&&cross(S[top].p-S[top-1].p,p[i].p-S[top-1].p)<=0)
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

int n;
double ans[MAXN];

int main(void){
	scanf("%d",&n);
	if(n==1)
		puts("1");
	else if(n==2)
		puts("0.5\n0.5");
	else{
		vector<Node> S(n);
		for(reg int i=0;i<n;++i)
			S[i].id=i,scanf("%lf%lf",&S[i].p.x,&S[i].p.y);
		S=getCon(S);
		if(S.size()==2)
			ans[S[0].id]=ans[S[1].id]=0.5;
		else
			for(reg int i=0,siz=S.size();i<siz;++i){
				Vector v1=S[(i+1)%siz].p-S[i].p,v2=S[(i+siz-1)%siz].p-S[i].p;
				ans[S[i].id]=0.5-acos(dot(v1,v2)/v1.len()/v2.len())/(2*pi);
			}
		for(reg int i=0;i<n;++i)
			printf("%.10lf\n",ans[i]);
	}
	return 0;
}