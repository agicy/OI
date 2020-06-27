#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;

int n;
double p[MAXN],x1[MAXN],x2[MAXN],ans[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		scanf("%lf",&p[i]);
		x1[i]=(x1[i-1]+1)*p[i];
		x2[i]=(x2[i-1]+2*x1[i-1]+1)*p[i];
	}
	for(reg int i=1;i<=n;++i)
		ans[i]=ans[i-1]+(3*x2[i-1]+3*x1[i-1]+1)*p[i];
	printf("%.1lf\n",ans[n]);
	return 0;
}