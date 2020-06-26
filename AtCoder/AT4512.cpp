#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=500+5;

int n,K;
int a[MAXN][MAXN];

int main(void){
	scanf("%d",&K);
    if(K<=500){
    	printf("%d\n",K);
    	for(reg int i=1;i<=K;++i)
    		for(reg int j=1;j<=K;++j)
				printf("%d%c",i,j==K?'\n':' ');
	}
	else{
		n=500;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				a[i][j]=(i+j)%n+1;
		for(reg int i=n+1;i<=K;++i)
			for(reg int j=0;j<n;++j)
				if((j&1)==0)
					a[(i-1-j+n)%n][j]=i;
		printf("%d\n",n);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				printf("%d%c",a[i][j],j==n-1?'\n':' ');
	}
	return 0;
}
