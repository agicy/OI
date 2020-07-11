#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

struct Node{
	ll x,y;
	inline void Read(void){
		scanf("%lld%lld",&x,&y);
		return;
	}
};

const int MAXN=100+5;

int n;
Node a[MAXN];

int main(void){
	reg int ans=0;
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			for(reg int k=j+1;k<=n;++k){
				reg ll V1x=a[i].x-a[j].x,V1y=a[i].y-a[j].y;
				reg ll V2x=a[i].x-a[k].x,V2y=a[i].y-a[k].y;
				reg ll S=abs(V1x*V2y-V2x*V1y);
				if(S!=0&&S%2==0)
					++ans;
			}
	printf("%d\n",ans);
	return 0;
}
