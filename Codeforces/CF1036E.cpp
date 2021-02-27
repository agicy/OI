#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;

struct Segment{
	int x1,y1,x2,y2;
};

struct Line{
	ll A,B,C;
	inline Line(void){}
	inline Line(const Segment& l){
		A=l.y1-l.y2;
		B=l.x2-l.x1;
		C=-A*l.x1-B*l.y1;
		return;
	}
};

int n;
Segment l[MAXN];

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline int get(const Segment& l){
	return gcd(abs(l.x1-l.x2),abs(l.y1-l.y2))+1;
}

inline ll cross(reg ll a,reg ll b,reg ll c,reg ll d){
	return a*d-b*c;
}

inline bool check(reg int x,reg int l,reg int r){
	if(l>r)
		return r<=x&&x<=l;
	else
		return l<=x&&x<=r;
}

inline bool getPoint(Segment l,Segment b,int& x,int& y){
	Line l1(l),l2(b);
	reg ll dx=cross(l1.C,l1.B,l2.C,l2.B),dy=cross(l1.A,l1.C,l2.A,l2.C),d=cross(l1.A,l1.B,l2.A,l2.B);
	if(!d)
		return false;
	if(dx%d||dy%d)
		return false;
	x=-dx/d,y=-dy/d;
	if(!check(x,l.x1,l.x2)||!check(y,l.y1,l.y2))
		return false;
	if(!check(x,b.x1,b.x2)||!check(y,b.y1,b.y2))
		return false;
	return true;
}

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		l[i].x1=read(),l[i].y1=read(),l[i].x2=read(),l[i].y2=read();
	reg int ans=0;
	for(reg int i=0;i<n;++i){
		ans+=get(l[i]);
		set<pair<int,int>/**/> S;
		int x,y;
		for(reg int j=0;j<i;++j)
			if(getPoint(l[i],l[j],x,y))
				S.insert(make_pair(x,y));
		ans-=S.size();
	}
	printf("%d\n",ans);
	return 0;
}