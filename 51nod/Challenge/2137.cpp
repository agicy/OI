#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;

int main(void){
	scanf("%d",&n);
	reg int f1=3,f2=4;
	reg double sum=0;
	for(reg int i=1;i<=n;++i){
		reg int t1=f2,t2=f1+f2;
		f1=t1,f2=t2;
		sum+=1.0*f1/f2;
	}
	printf("%d/%d\n%.2lf\n",f1,f2,sum);
	return 0;
}