#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1e5+5;
const int s=13;

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

inline double sqr(reg double x){
	return x*x;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=0;i<n;++i)
		a[i].Read();
	sort(a,a+n);
	double Min=1e20,Max=0;
	for(reg int i=0;i<n;++i){
		for(reg int j=i+1;j<n&&j<i+s;++j)
			Min=min(Min,sqr(a[i].x-a[j].x)+sqr(a[i].y-a[j].y));
		for(reg int j=n-1;j>=i&&j>=n-s;--j)
			Max=max(Max,sqr(a[i].x-a[j].x)+sqr(a[i].y-a[j].y));
	}
	printf("%.2f %.2f\n",sqrt(Min),sqrt(Max));
	return 0;
}