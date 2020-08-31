#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e3+5;

int n;
int a[MAXN];
int f[MAXN];

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	int ans=0;
	for(int i=1;i<=n;++i){
		f[i]=1;
		for(int j=1;j<i;++j)
			if(a[j]<a[i])
				f[i]=max(f[i],f[j]+1);
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return 0;
}