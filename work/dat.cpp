#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m;
int a[MAXN],b[MAXM];

int main(void){
	srand(time(0));
	n=myrand(1,10),m=myrand(1,10);
	for(reg int i=1;i<=n;++i)
		a[i]=myrand(-1e9,1e9);
	for(reg int j=1;j<=m;++j)
		b[j]=myrand(-1e9,1e9);
	printf("%d %d\n",n,m);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i],i==n?'\n':' ');
	for(reg int i=1;i<=m;++i)
		printf("%d%c",b[i],i==m?'\n':' ');
	return 0;
}