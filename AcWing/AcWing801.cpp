#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int lowbit(reg int x){
	return x&(-x);
}

inline int cnt(reg int x){
	reg int res=0;
	while(x){
		++res;
		x-=lowbit(x);
	}
	return res;
}

int main(void){
	int n;
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d",&x);
		printf("%d%c",cnt(x),i==n?'\n':' ');
	}
	return 0;
}