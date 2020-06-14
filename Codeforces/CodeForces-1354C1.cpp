#include<bits/stdc++.h>
using namespace std;
#define reg register

const double PI=acos(-1.0);

int n;

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		if(n&1){
			reg double ans=cos(PI/n*0.25)/sin(PI/n*0.5);
			printf("%.10lf\n",ans);
		}
		else{
			reg double angle=PI/n;
			printf("%.10lf\n",sin(angle)/(1-cos(angle)));
		}
	}
	return 0;
}