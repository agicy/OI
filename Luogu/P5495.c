#include<stdio.h>
#include<stdbool.h>
#define reg register

#define getnext() (seed^=seed<<13,seed^=seed>>17,seed^=seed<<5,seed)

#define MAXN 20000005

unsigned n,seed;
unsigned a[MAXN];
bool vis[MAXN];
unsigned tot,prime[1270607];

int main(void){
	scanf("%u%u",&n,&seed);
	reg unsigned i,j,k;
	for(i=2;i<=n;++i){
		if(!vis[i])
			prime[tot++]=i;
		for(j=0;j<tot&&(k=i*prime[j],k<=n);++j){
			vis[k]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	for(i=1;i<=n;++i)
		a[i]=getnext();
	for(i=0;i<tot;++i)
		for(j=1;k=j*prime[i],k<=n;++j)
			a[k]+=a[j];
	reg unsigned ans=0;
	for(i=1;i<=n;++i)
		ans^=a[i];
	printf("%u\n",ans);
	return 0;
}