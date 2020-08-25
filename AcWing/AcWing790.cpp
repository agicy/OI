#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	double n;
	scanf("%lf",&n);
	printf("%.6lf\n",n<0?-pow(-n,1.0/3.0):pow(n,1.0/3.0));
	return 0;
}