#include<stdio.h>
#include<bitset>
using std::bitset;
void fun(int n){
	bitset<sizeof(int)*8>num(n);
	bool flag=false;
	for(int i=31;i>=0;i--)
		if(num[i]&&flag==false){
			if(i>2){
				printf("2(");
				fun(i);
				printf(")");
			}
			else{
				if(i==1)
					printf("2");
				else
					printf("2(%d)",i);
			}
			flag=true;
		}
		else if(num[i])
			if(i>2){
				printf("+2(");
				fun(i);
				printf(")");
			}
			else
				if(i==1)
					printf("+2");
				else
					printf("+2(%d)",i);
}
int main(void){
	int n;
	scanf("%d",&n);
	//bitset<sizeof(int)*8>num(n);
	fun(n);
	return 0;
}