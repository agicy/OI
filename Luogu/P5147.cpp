#include<bits/stdc++.h>
using namespace std;
#define reg register

int n;

int main(void){
	scanf("%d",&n);
	reg double ans=0,sum=0;
	for(reg int i=2;i<=n;++i){
		ans=(1.0+sum/i)*i/(i-1);
		sum+=ans;
	}
	printf("%.5f\n",ans);
	return 0;
}
