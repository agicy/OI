#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

namespace TreeArray{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int S){
		n=S;
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
vector<int> V;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	reg ll ans=0;
	TreeArray::Init(n);
	for(reg int i=n;i>=1;--i){
		ans+=TreeArray::query(a[i]-1);
		TreeArray::update(a[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}