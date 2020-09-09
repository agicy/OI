#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const double eps=1e-6;

int n,k;
int a[MAXN],b[MAXN];

inline bool check(reg double x){
	static double tmp[MAXN];
	for(reg int i=1;i<=n;++i)
		tmp[i]=a[i]-x*b[i];
	sort(tmp+1,tmp+n+1);
	reg double sum=0;
	for(reg int i=k+1;i<=n;++i)
		sum+=tmp[i];
	return sum>=0;
}

int main(void){
	while(scanf("%d%d",&n,&k)!=EOF&&(n!=0||k!=0)){
		for(reg int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		for(reg int i=1;i<=n;++i)
			scanf("%d",&b[i]);
		reg double l=0,r=100,mid;
		while(r-l>eps){
			mid=0.5*(l+r);
			if(check(mid))
				l=mid;
			else
				r=mid;
		}
		printf("%.0lf\n",100.0*l);
	}
	return 0;
}