#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

int n,m,x;
int a[MAXN],b[MAXN];

int main(void){
	scanf("%d%d%d",&n,&m,&x);
	for(int i=0;i<n;++i)
		scanf("%d",&a[i]);
	for(int j=0;j<m;++j)
		scanf("%d",&b[j]);
	for(int i=0,j=m-1;i<n;++i){
		while(j>=0&&a[i]+b[j]>x)
			--j;
		if(a[i]+b[j]==x){
			printf("%d %d\n",i,j);
			return 0;
		}
	}
	return 0;
}