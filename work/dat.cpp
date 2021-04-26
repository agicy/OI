#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m,p;
int a[MAXN];
int l[MAXM],r[MAXM];

int main(void){
	srand(time(0));
	n=myrand(1,5e3),m=myrand(1,5e3),p=1;
	for(reg int i=1;i<=n;++i)
		a[i]=myrand(1,1e5);
	for(reg int i=1;i<=m;++i)
		l[i]=myrand(1,n),r[i]=myrand(1,n);
	printf("%d %d %d\n",n,m,p);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i],i==n?'\n':' ');
	for(reg int i=1;i<=m;++i)
		printf("1\n%d %d\n",min(l[i],r[i]),max(l[i],r[i]));

	return 0;
}