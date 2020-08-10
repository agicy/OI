#include<stdio.h>
int num[9]= {0};
int main(void) {
	int j,k;
	for (int i=123;i*3<=987;i++){
		for (int b=0; b<9; b++)
			num[b]=0;
		num[i/100-1]++;
		num[i/10%10-1]++;
		num[i%10-1]++;
		j = i*2;
		num[j/100-1]++;
		num[j/10%10-1]++;
		num[j%10-1]++;
		k = i*3;
		num[k/100-1]++;
		num[k/10%10-1]++;
		num[k%10-1]++;
		for (int a=0;a<9;a++){
			if (num[a]!=1){
				break;
			}
			if(a==8){
				printf("%d %d %d\n",i,j,k);
			}
		}
	}
	return 0;
}