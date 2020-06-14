#include<bits/stdc++.h>
using namespace std;
#define reg register

long double a;

inline long double f(reg long double x){
	return pow(x,a/x-x);
}

inline long double simpson(reg long double l,reg long double r){
	reg long double mid=(l+r)*0.5;
	return (r-l)*(f(l)+4*f(mid)+f(r))/6.0;
}

inline long double asr(reg long double l,reg long double r,reg double eps,reg double ans){
	reg long double mid=(l+r)*0.5;
	reg long double left=simpson(l,mid),right=simpson(mid,r);
	if(abs(left+right-ans)<=15*eps)
		return left+right-(left+right-ans)/15;
	else
		return asr(l,mid,eps*0.5,left)+asr(mid,r,eps*0.5,right);
}

int main(void){
	scanf("%Lf",&a);
	if(a<0)
		puts("orz");
	else{
		reg long double ans=asr(1e-8,15,1e-8,simpson(1e-8,15));
		printf("%.5Lf\n",ans);
	}
	return 0;
}