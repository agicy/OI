#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d",&x);
		reg int res=x;
		for(reg int i=2;1ll*i*i<=x;++i)
			if(x%i==0){
				res=res/i*(i-1);
				while(x%i==0)
					x/=i;
			}
		if(x>1)
			res=res/x*(x-1);
		printf("%d\n",res);
	}
	return 0;
}