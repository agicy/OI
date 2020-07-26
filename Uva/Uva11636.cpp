#include <cmath>
#include <cstdio>

int n;

int main(void){
	register int Case=0;
	while(scanf("%d",&n)!=EOF){
		if(n<0)
			return 0;
		else
			printf("Case %d: %.0f\n", ++Case, ceil(log2(n)));
	}
	return 0;
}