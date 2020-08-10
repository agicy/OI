#include<stdio.h>
#include<iostream>
int main(void){
	int n,l;
	scanf("%d%d",&l,&n);
	int maxtime=0,mintime=0;
	for(int i=0;i<n;i++){
		int temp;
		scanf("%d",&temp);
		maxtime=std::max(maxtime,std::max(l-temp+1,temp));
		mintime=std::max(mintime,std::min(l-temp+1,temp));
	}
	printf("%d %d",mintime,maxtime);
	return 0;
}