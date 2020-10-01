#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;

int n;
int a[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<i;++j)
			if(a[j]>a[i])
				++ans;
	printf("%d\n",ans);
	return 0;
}