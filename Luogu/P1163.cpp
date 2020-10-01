#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const double eps=1e-5;

double n,m,k;

inline bool check(reg double mid){
	return (pow(1.0/(1.0+mid),k)>=1-n/m*mid);
}

int main(void){
	scanf("%lf%lf%lf",&n,&m,&k);
	reg double l=0,r=10,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%.1lf\n",100.0*l);
	return 0;
}