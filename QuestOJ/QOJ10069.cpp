#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;
const double eps=1e-8;

inline double max(reg double a,reg double b){
	return a>b?a:b;
}

inline double sgn(reg double x){
	if(fabs(x)<eps)
		return x;
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

inline bool cmp(const Point& a,const Point& b){
	return a.x<b.x||(sgn(a.x-b.x)==0&&a.y<b.y);
}

int n;
Point p[MAXN];
int tot;
Point q[MAXN];
bool vis[MAXN];

inline double getS(const Point& a,const Point& b,const Point& c,const Point& d){
	return 0.5*fabs(cross(a-c,b-d));
}

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
	for(reg int i=0;i<top;++i){
		q[i]=p[S[i+1]];
		vis[S[i+1]]=true;
	}
	tot=top;
	reg double ans=0;
	if(top<=2)
		ans=0;
	else if(top==3){
		for(reg int i=1;i<=n;++i)
			if(!vis[i])
				ans=max(
					max(ans,getS(q[0],q[2],q[1],p[i])),
					max(getS(q[0],q[1],q[2],p[i]),getS(q[1],q[0],p[i],q[2]))
				);
	}
	else{
		reg int j=1,k=1,l=1;
		for(reg int i=0;i<tot;++i){
			while(cross(q[i+1]-q[i],q[j+1]-q[i])>cross(q[i+1]-q[i],q[j]-q[i]))
				j=(j+1)%tot;
			while(cross(q[i]-q[j],q[k+1]-q[j])>cross(q[i]-q[j],q[k]-q[j]))
				k=(k+1)%tot;
			if(!i)
				l=j;
			while(cross(q[i]-q[l+1],q[j]-q[l+1])>cross(q[i]-q[l],q[j]-q[l]))
				l=(l+1)%tot;
			ans=max(ans,max(getS(q[i],q[k],q[j],q[l]),getS(q[i+1],q[k],q[j],q[l])));
		}
	}
	printf("%.3lf\n",ans);
	return 0;
}