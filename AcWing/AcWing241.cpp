#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;

namespace BIT{
	inline int lowbit(int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(int id,int val){
		for(int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(int id){
		int res=0;
		for(int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int n;
int y[MAXN];
int l[MAXN],r[MAXN];

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&y[i]);
	ll ans1=0,ans2=0;
	BIT::Init(n);
	for(int i=n;i>=1;--i){
		r[i]=n-i-BIT::query(y[i]);
		BIT::update(y[i],1);
	}
	BIT::Init(n);
	for(int i=1;i<=n;++i){
		l[i]=i-1-BIT::query(y[i]);
		BIT::update(y[i],1);
	}
	for(int i=1;i<=n;++i)
		ans1+=1ll*l[i]*r[i];
	BIT::Init(n);
	for(int i=n;i>=1;--i){
		r[i]=BIT::query(y[i]);
		BIT::update(y[i],1);
	}
	BIT::Init(n);
	for(int i=1;i<=n;++i){
		l[i]=BIT::query(y[i]);
		BIT::update(y[i],1);
	}
	for(int i=1;i<=n;++i)
		ans2+=1ll*l[i]*r[i];
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}