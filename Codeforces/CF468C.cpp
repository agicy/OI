#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const ll I=1e18;

ll a;

int main(void){
	scanf("%lld",&a);
	printf("%lld %lld\n",a-I%a*9%a*9%a,a-I%a*9%a*9%a+I-1);
	return 0;
}