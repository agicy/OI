#include <cstdio>

int x;

int main(void){
	register int cnt=0;
	scanf("%d",&x);
	while(x){
		if(x&1)
			++cnt;
		x>>=1;
	}
	printf("%d\n",cnt);
	return 0;
}