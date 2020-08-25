#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n,k;
int a[MAXN];

int main(void){
	scanf("%d%d",&n,&k);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	nth_element(a+1,a+k,a+n+1);
	printf("%d\n",a[k]);
	return 0;
}