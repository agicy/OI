#include<bits/stdc++.h>
using namespace std;
#define reg register

long double a,b,c,d,L,R;

inline long double f(reg long double x){
	return (c*x+d)/(a*x+b);
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
	scanf("%Lf%Lf%Lf%Lf%Lf%Lf",&a,&b,&c,&d,&L,&R);
	reg long double ans=asr(L,R,1e-8,simpson(L,R));
	printf("%.6Lf\n",ans);
	return 0;
}