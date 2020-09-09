#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=5e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0x3f,sizeof(unit));
		return;
	}
	inline void update(reg int id,ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=min(unit[i],val);
		return;
	}
	inline ll query(reg int id){
		ll res=inf;
		for(reg int i=id;i;i-=lowbit(i))
			res=min(res,unit[i]);
		return res;
	}
};

int n;
int h[MAXN];
vector<int> V;
ll sum[MAXN];
BIT T1,T2;
int p[MAXN];
ll g[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		scanf("%d",&h[i]);
		V.push_back(h[i]);
		sum[i]=sum[i-1]+abs(h[i]-h[i-1]);
	}
	V.push_back(0);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n+1;++i)
		p[i]=lower_bound(V.begin(),V.end(),h[i-1])-V.begin()+1;
	reg int m=V.size();
	ll ans=inf;
	T1.Init(n+1),T2.Init(n+1);
	g[1]=h[1];
	T1.update(p[1],0),T2.update(m-p[1]+1,0);
	ans=min(ans,g[1]+sum[n]-sum[1]);
	for(reg int i=2;i<=n;++i){
		g[i]=min(T1.query(p[i+1])+h[i],T2.query(m-p[i+1]+1)-h[i])+sum[i-1];
		T1.update(p[i],g[i]-sum[i]-h[i-1]);
		T2.update(m-p[i]+1,g[i]-sum[i]+h[i-1]);
		ans=min(ans,g[i]+sum[n]-sum[i]);
	}
	printf("%lld\n",ans);
	return 0;
}