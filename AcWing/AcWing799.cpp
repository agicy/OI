#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
const int MAXA=1e5+5;

int n;
int a[MAXN];
int T[MAXA];

int main(void){
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&a[i]);
	int ans=0;
	for(int i=0,j=0;i<n;++i){
		++T[a[i]];
		while(T[a[i]]>1)
			--T[a[j++]];
		ans=max(ans,i-j+1);
	}
	printf("%d\n",ans);
	return 0;
}