#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;

struct BIT{
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
};

int n;
int a[MAXN];
BIT T;
int l[MAXN],r[MAXN];

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	T.Init(n);
	for(int i=1;i<=n;++i){
		l[i]=T.query(a[i]-1);
		T.update(a[i],1);
	}
	T.Init(n);
	for(int i=n;i>=1;--i){
		r[i]=T.query(n)-T.query(a[i]);
		T.update(a[i],1);
	}
	ll ans=0;
	T.Init(n);
	for(int i=n;i>=1;--i){
		int tmp=T.query(n)-T.query(a[i]);
		ans+=1ll*tmp*(tmp-1)/2;
		T.update(a[i],1);
	}
	for(int i=1;i<=n;++i)
		ans-=1ll*l[i]*r[i];
	printf("%lld\n",ans);
	return 0;
}