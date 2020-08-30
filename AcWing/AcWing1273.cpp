#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;
const int MAXLOG2N=18+1;

int n,m,a[MAXN];

namespace ST{
	int Lg[MAXN];
	int Max[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Max[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				Max[j][i]=max(Max[j-1][i],Max[j-1][i+(1<<(j-1))]);
		return;
	}
	inline int query(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		return max(Max[k][l],Max[k][r-(1<<k)+1]);
	}
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	ST::Init(n,a);
	scanf("%d",&m);
	for(reg int i=1;i<=m;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",ST::query(a,b));
	}
	return 0;
}