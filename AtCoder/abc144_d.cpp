#include<cstdio>
#include<cmath>
#define reg register

const double PI=acos(-1);

double a,b,x;

inline void Read(void);

int main(void){
	reg double y,ans;
	scanf("%lf%lf%lf",&a,&b,&x);
	if(a*b/2.0*a>=x){
		y=((2.0*x)/(a*b));
		ans=atan(b/y)/PI*180.0;
	}
	else{
		y=2*x/(a*a)-b;
		ans=atan((b-y)/a)/PI*180;
	}
	printf("%.10f\n",ans);
	return 0;
}