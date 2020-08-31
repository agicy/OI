#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

namespace BIT{
	inline int lowbit(int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(int id,ll val){
		for(int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(int id){
		ll res=0;
		for(int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int n,m;
ll a[MAXN],b[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	BIT::Init(n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		b[i]=a[i]-a[i-1];
		BIT::update(i,b[i]);
	}
	for(int i=1;i<=m;++i){
		static char op;
		cin>>op;
		static ll l,r,d,x;
		if(op=='C'){
			scanf("%lld%lld%lld",&l,&r,&d);
			BIT::update(l,d),BIT::update(r+1,-d);
		}
		else if(op=='Q'){
			scanf("%d",&x);
			printf("%lld\n",BIT::query(x));
		}
	}
	return 0;
}