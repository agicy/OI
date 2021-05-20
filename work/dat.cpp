#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n;

int main(void){
	srand(time(0));
	n=myrand(1,500);
	printf("%d\n",n);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",myrand(1,i),i==n?'\n':' ');
	return 0;
}