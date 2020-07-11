#include<bits/stdc++.h>
using namespace std;
#define reg register

int x;

int main(void){
	scanf("%d",&x);
	reg bool flag1=!(x&1);
	reg bool flag2=(x>4)&&(x<=12);
	reg int ans1=flag1&&flag2;
	reg int ans2=flag1||flag2;
	reg int ans3=flag1^flag2;
	reg int ans4=((flag1||flag2)==false);
	printf("%d %d %d %d\n",ans1,ans2,ans3,ans4);
	return 0;
}
