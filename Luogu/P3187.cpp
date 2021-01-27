#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=5e4+5;
const double inf=1e20;
const double eps=1e-8;

inline double sgn(reg double x){
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
	inline Vector operator*(reg double a)const{
		return Vector(x*a,y*a);
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
	return a.x<b.x||(sgn(a.x-b.x)==0&&a.y<b.y);
}

inline double getL(const Point& a,const Point& b){
	return sqrt(dot(a-b,a-b));
}
inline double getS(const Point& a,const Point& b,const Point& c){
	return fabs(cross(b-a,c-a));
}

int n;
Point p[MAXN];
int tot;
Point q[MAXN];
Point Ans[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp);
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i){
		while(top>1&&sgn(cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top-1]]))<=0)
			--top;
		S[++top]=i;
	}
	reg int tmp=top;
	for(reg int i=n-1;i>=1;--i){
		while(top>tmp&&sgn(cross(p[S[top]]-p[S[top-1]],p[i]-p[S[top-1]]))<=0)
			--top;
		S[++top]=i;
	}
	if(n>1)
		--top;
	for(reg int i=0;i<top;++i)
		q[i]=p[S[i+1]];
	tot=top;
	q[tot]=q[0];
	reg int j=1,k=1,l=1;
	reg double ans=inf;
	for(reg int i=0;i<tot;++i){
		while(cross(q[i+1]-q[i],q[j+1]-q[i])>cross(q[i+1]-q[i],q[j]-q[i]))
			j=(j+1)%tot;
		if(i==0)
			l=j;
		while(dot(q[l+1]-q[i+1],q[i]-q[i+1])>dot(q[l]-q[i+1],q[i]-q[i+1]))
			l=(l+1)%tot;
		while(dot(q[k+1]-q[i],q[i+1]-q[i])>dot(q[k]-q[i],q[i+1]-q[i]))
			k=(k+1)%tot;
		reg double len=getL(q[i+1],q[i]);
		reg double lef=dot(q[l]-q[i+1],q[i]-q[i+1])/len;
		reg double rig=dot(q[k]-q[i],q[i+1]-q[i])/len;
		reg double h=getS(q[i+1],q[i],q[j])/len;
		reg double tmp=(lef+rig-len)*h;
		if(tmp<ans){
			ans=tmp;
			Ans[0]=q[i+1]-(q[i+1]-q[i])*(lef/len);
			Ans[1]=Ans[0]+(q[i+1]-q[i])*((rig+lef-len)/len);
			Ans[2]=Ans[1]+(q[k]-Ans[1])*(h/getL(q[k],Ans[1]));
			Ans[3]=Ans[2]+(q[i]-q[i+1])*((rig+lef-len)/len);
		}
	}
	printf("%.5lf\n",ans);
	reg int ptr=0;
	for(reg int i=1;i<4;++i)
		if(Ans[i].y<Ans[ptr].y||(Ans[i].y==Ans[ptr].y&&Ans[i].x<Ans[ptr].x))
			ptr=i;
	if(!sgn(Ans[ptr].x))
		Ans[ptr].x=0;
	if(!sgn(Ans[ptr].y))
		Ans[ptr].y=0;
	printf("%.5lf %.5lf\n",Ans[ptr].x,Ans[ptr].y);
	for(reg int i=1;i<=3;++i){
		if(!sgn(Ans[(i+ptr)%4].x))
			Ans[(i+ptr)%4].x=0;
		if(!sgn(Ans[(i+ptr)%4].y))
			Ans[(i+ptr)%4].y=0;
		printf("%.5lf %.5lf\n",Ans[(i+ptr)%4].x,Ans[(i+ptr)%4].y);
	}
	return 0;
}