#include<stdio.h>
int main(void){
	int n;
	scanf("%d",&n);
	int temp=0,s;
	for(s=0;s<n;temp+=1,s+=temp);
	if(temp%2==1)
		printf("%d/%d",s-n+1,temp+n-s);
	else
		printf("%d/%d",temp+n-s,s-n+1);
	return 0;
}