#include<cstdio>

bool isNPrime[1000000+5];
int n;
int cnt,Prime[1000000+5];

void Eratosthenes(void);

int main(void){
	register int i;
	Eratosthenes();
	while(scanf("%d",&n)!=EOF&&n){
		for(i=1;i<=cnt;++i){
			if((Prime[i]&1)&&Prime[i]<n&&!isNPrime[n-Prime[i]]){
				printf("%d = %d + %d\n",n,Prime[i],n-Prime[i]);
				break;
			}
		}
	}
	return 0;
}

void Eratosthenes(void){
	register int i,j;
	for(i=2;i<=1000000;++i){
		if(!isNPrime[i]){
			Prime[++cnt]=i;
			for(j=(i<<1);j<=1000000;j+=i){
				isNPrime[j]=true;
			}
		}
	}
	return;
}
