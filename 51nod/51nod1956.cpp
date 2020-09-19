#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	int n;
	cin>>n;
	reg bool flag=false;
	for(reg int o=2;o<=n;++o)
		for(reg int r=2;r<o;++r)
			for(reg int s=r+1;s<o;++s)
				for(reg int t=s+1;t<o;++t)
					if(o*o*o==r*r*r+s*s*s+t*t*t){
						flag=true;
						printf("(%d,%d,%d,%d)\n",o,r,s,t);
					}
	if(!flag)
		puts("OMG");
	return 0;
}