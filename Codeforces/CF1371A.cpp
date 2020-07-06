#include<bits/stdc++.h>
using namespace std;

int n;

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		printf("%d\n",((n&1)?(n+1):(n))>>1);
	}
	return 0;
}