#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i,putchar('\n'))
		for(reg int j=1;j<=i;++j)
			putchar('*');
	return 0;
}