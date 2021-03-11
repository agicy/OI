#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

const int MAXN=5e4+5;
const int MAXQ=5e4+5;

int main(void){
	FILE* x=fopen("tmp","r");
	int tmp;
	fscanf(x,"%d",&tmp);
	fclose(x);

	x=fopen("tmp","w");
	fprintf(x,"%d\n",tmp+1);
	fclose(x);

	srand(time(0));
	int S=tmp;
	printf("%d\n",10);
	for(reg int i=0;i<10;++i)
		putchar(((S>>i)&1)+'0');
	return 0;
}