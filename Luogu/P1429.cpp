#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 1e18

struct Node{
	double x,y;
	inline void Read(void){
		scanf("%lf%lf",&x,&y);
		return;
	}
};

inline bool cmpx(const Node& a,const Node& b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}

inline bool cmpy(const Node& a,const Node& b){
	return a.y==b.y?a.x<b.x:a.y<b.y;
}

inline double Dis(const Node& a,const Node& b){
	reg double dx=a.x-b.x,dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

const int MAXN=200000+5;

int n;
Node p[MAXN],temp[MAXN];

inline void Read(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		p[i].Read();
	return;
}

inline double Solve(reg int l,reg int r){
	if(l==r)
		return INF;
	else if(r-l==1)
		return Dis(p[l],p[r]);
	reg int mid=(l+r)>>1;
	reg double ans=min(Solve(l,mid),Solve(mid,r));
	reg int cnt=0;
	for(reg int i=l;i<=r;++i)
		if(fabs(p[i].x-p[mid].x)<=ans)
			temp[++cnt]=p[i];
	sort(temp+1,temp+cnt+1,cmpy);
	for(reg int i=1;i<=cnt;++i)
		for(reg int j=i+1;j<=cnt&&fabs(temp[i].y-temp[j].y)<ans;++j)
			ans=min((double)ans,Dis(temp[i],temp[j]));
	return ans;
}

inline void Work(void){
	sort(p+1,p+n+1,cmpx);
	printf("%.4f\n",Solve(1,n));
	return;
}
