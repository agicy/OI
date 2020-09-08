#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;
const int MAXM=2e5+5;

struct querys{
	int l,r,id,bl;
	inline querys(reg int l=0,reg int r=0,reg int id=0,reg int bl=0):l(l),r(r),id(id),bl(bl){
		return;
	}
	inline bool operator<(const querys& a)const{
		return bl==a.bl?r<a.r:bl<a.bl;
	}
};

int n,m;
int a[MAXN];
int B;
int Ans;
int cnt[MAXN<<1];
int ans[MAXM];
querys Q[MAXM];

inline void del(reg int x){
	--cnt[a[x]];
	if(!cnt[a[x]])
		Ans=min(Ans,a[x]);
	return;
}

inline void add(reg int x){
	++cnt[a[x]];
	while(cnt[Ans])
		++Ans;
	return;
}

vector<int> V;

int main(void){
	scanf("%d%d",&n,&m);
	reg int B=sqrt(n);
	for(reg int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		V.push_back(a[i]);
		V.push_back(a[i]+1);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin();
	for(reg int i=1;i<=m;++i){
		static int l,r;
		scanf("%d%d",&l,&r);
		Q[i]=querys(l,r,i,(l-1)/B+1);
	}
	reg int l=1,r=0;
	sort(Q+1,Q+m+1);
	for(reg int i=1;i<=m;++i){
		while(r<Q[i].r)
			add(++r);
		while(r>Q[i].r)
			del(r--);
		while(l<Q[i].l)
			del(l++);
		while(l>Q[i].l)
			add(--l);
		ans[Q[i].id]=V[Ans];
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}