#include<bits/stdc++.h>
using namespace std;

double a,b,c;

int main(void){
	scanf("%lf%lf%lf",&a,&b,&c);
	double p=(a+b+c)*0.5;
	printf("%.1lf\n",sqrt(p*(p-a)*(p-b)*(p-c)));
	return 0;
}
