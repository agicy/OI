#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define double long double

const int MAXN=5e5+5;

int n,m;
double p;
vector<int> G[MAXN];

inline double fpow(reg double x,reg int exp){
	reg double res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x;
		exp>>=1;
	}
	return res;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	double unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg double val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline double query(reg int id){
		reg double res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline double query(reg int l,reg int r){
		if(r>n) r=n;
		if(l>n) l=n;
		return query(r)-query(l-1);
	}
}

int main(void){
	scanf("%d%d%Lf",&n,&m,&p);
	for(reg int i=1;i<=m;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
	}
	BIT::Init(n);
	reg double ans=0;
	for(reg int i=1;i<=n;++i)
		if(G[i].size()){
			sort(G[i].begin(),G[i].end());
			reg double poss=p/(1.0-fpow(1.0-p,G[i].size()));
			for(reg int j=0,siz=G[i].size();j<siz;++j){
				reg double res=BIT::query(n-G[i][j]);
				ans+=poss*res;
				BIT::update(n-G[i][j]+1,poss);
				poss=poss*(1.0-p);
			}
		}
	printf("%.2Lf\n",ans);
	return 0;
}