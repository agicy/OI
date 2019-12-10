#include<cstdio>
#include<cmath>
#include<algorithm>
using std::min;
using std::sort;
#define reg register
#define INF 1e18

const int MAXN=200000+5;

struct Node{
	double x,y;
	inline void Read(void){
		scanf("%lf%lf",&x,&y);
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x;
	}
};

int n;
Node a[MAXN];

inline void Read(void);
inline void Work(void);
inline double Solve(reg int,reg int);
inline double Dis(Node&,Node&b);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	reg int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
		a[i].Read();
	return;
}

inline void Work(void){
	sort(a+1,a+n+1);
	double ans=Solve(1,n);
	printf("%.4f\n",ans);
	return;
}

inline double Solve(reg int l,reg int r){
	if(l==r)
		return INF;
	if(l==r-1)
		return Dis(a[l],a[r]);
	reg int mid=(l+r)>>1;
	double ans1=Solve(l,mid);
	double ans2=Solve(mid+1,r);
	reg double ans=min(ans1,ans2);
	reg int i,j;
	reg int left=l,right=r;
	while(left<=mid&&(a[mid].x-a[left].x)>ans)
		++left;
	while(right>mid&&(a[right].x-a[mid+1].x)>ans)
		--right;
	for(i=left;i<=mid;++i)
		for(j=mid+1;j<=right;++j)
			if(abs(a[i].y-a[j].y)>ans)
				continue;
			else
				ans=min((double)ans,Dis(a[i],a[j]));
	return ans;
}

inline double Dis(Node& a,Node& b){
	reg double dx=a.x-b.x,dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

