#include<stdio.h>
int main(void){
	int car[20]={0,1};
	int a,n,m,x;
	scanf("%d%d%d%d",&a,&n,&m,&x);
	for(int i=2;i<n;i++)
		car[i]=car[i-1]+car[i-2];
	int temp=(m-car[n-3]*a-a)/(car[n-2]-1);
	if(x==1)
		printf("%d",a);
	else
		printf("%d",car[x-2]*a+a+car[x-1]*temp-temp);
	return 0;
}