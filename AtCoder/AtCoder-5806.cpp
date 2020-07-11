#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll a,b,c;

int main(void){
	scanf("%lld%lld%lld",&a,&b,&c);
	if(c<a+b)
		puts("No");
	else if((c-a-b)*(c-a-b)<=4*a*b)
		puts("No");
	else
		puts("Yes");
	return 0;
}
