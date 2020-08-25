#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n;
int a[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i],i==n?'\n':' ');
	return 0;
}