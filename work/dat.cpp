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

int n;
int h[MAXN];

int main(void){
	srand(time(0));

	n=myrand(1,400);
	for(reg int i=1;i<=n;++i)
		h[i]=myrand(1,n);
	printf("%d\n",n);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",h[i],i==n?'\n':' ');
	return 0;
}