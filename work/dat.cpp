#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;

int n,k;

int main(void){
	srand(time(0));
	n=myrand(2,20);
	if(n<=14)
		k=myrand(1,min((1<<n)-1,3000));
	else
		k=myrand(1,3000);
	printf("%d %d\n",n,k);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",myrand(1,5),i==n?'\n':' ');
	return 0;
}