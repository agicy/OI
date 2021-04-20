#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e4+5;
const double eps=1e-12;

int n;
double Eu;
double s[MAXN],k[MAXN],v[MAXN];

inline double getSum(reg double lamda){
	reg double sum=0;
	for(reg int i=1;i<=n;++i){
		reg double l=max(v[i],0.0),r=1e5,mid;
		reg double val=0.5/lamda/k[i];
		while(r-l>eps){
			mid=0.5*(l+r);
			if(mid*mid*(mid-v[i])>val)
				r=mid;
			else
				l=mid;
		}
		sum+=k[i]*(l-v[i])*(l-v[i])*s[i];
	}
	return sum;
}

int main(void){
	scanf("%d%lf",&n,&Eu);
	for(reg int i=1;i<=n;++i)
		scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
	reg double l=0,r=1e5,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(getSum(mid)<Eu)
			r=mid;
		else
			l=mid;
	}
	reg double lamda=l;
	reg double ans=0;
	for(reg int i=1;i<=n;++i){
		reg double l=max(v[i],0.0),r=1e5,mid;
		reg double val=0.5/lamda/k[i];
		while(r-l>eps){
			mid=0.5*(l+r);
			if(mid*mid*(mid-v[i])>val)
				r=mid;
			else
				l=mid;
		}
		ans+=s[i]/l;
	}
	printf("%.8lf\n",ans);
	return 0;
}