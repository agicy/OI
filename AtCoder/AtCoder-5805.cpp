#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned long long ull;

ull H,W;

int main(void){
	scanf("%llu%llu",&H,&W);
	reg ull ans=(H*W+1)/2;
	printf("%llu\n",ans);
	return 0;
}
