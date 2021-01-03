#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

int q;
ull fib[105];

inline ull getSum(reg ull pos){
	reg ull res=0;
	while(pos){
		reg int ptr=1;
		while(fib[ptr+2]<=pos)
			++ptr;
		pos-=fib[ptr+1];
		res+=fib[ptr];
	}
	return res;
}

int main(void){
	fib[1]=fib[2]=1;
	for(reg int i=3;i<100;++i)
		fib[i]=fib[i-1]+fib[i-2];
	scanf("%d",&q);
	while(q--){
		static ull l,r;
		scanf("%llu%llu",&l,&r);
		printf("%llu\n",getSum(r)-getSum(l-1));
	}
	return 0;
}