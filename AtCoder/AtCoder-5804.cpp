#include<bits/stdc++.h>
using namespace std;
#define reg register

const int a[]={1,1,1,2,1,2,1,5,2,2,1,5,1,2,1,14,1,5,1,5,2,2,1,15,2,2,5,4,1,4,1,51};

int K;

int main(void){
	scanf("%d",&K);
	printf("%d\n",a[K-1]);
	return 0;
}
