#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned long long ull;

ull n,k;

int main(void){
	scanf("%llu%llu",&n,&k);
	k^=(k>>1);
	for(reg ull i=n;i>=1;--i)
		if(k&(1ull<<(i-1)))
			putchar('1');
		else
			putchar('0');
	putchar('\n');
	return 0;
}
