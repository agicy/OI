#include<bits/stdc++.h>
using namespace std;
#define reg register

int n;

int main(void){
	scanf("%d",&n);
	reg double ans=0;
	if(n<100000)
		for(reg int i=1;i<n;++i)
			ans+=1.0/i;
	else
		ans=log(n)+0.577215664901532;
	printf("%.5f\n",n==1?0:ans+1);
	return 0;
}