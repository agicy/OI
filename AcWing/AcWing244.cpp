#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int n;
int a[MAXN];
int ans[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=2;i<=n;++i)
		scanf("%d",&a[i]);
	BIT::Init(n);
	for(reg int i=1;i<=n;++i)
		BIT::update(i,1);
	reg int l,r,mid;
	for(reg int i=n;i>=1;--i){
		l=1,r=n;
		while(l<r){
			mid=(l+r)>>1;
			if(BIT::query(mid)<a[i]+1)
				l=mid+1;
			else
				r=mid;
		}
		ans[i]=r;
		BIT::update(r,-1);
	}
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}