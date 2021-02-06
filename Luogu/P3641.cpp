#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const ll inf=2e18;

ll a[MAXN];

extern "C" void MinMax(ll,ll,ll*,ll*);
extern "C" ll findGap(int,int);

extern "C" ll findGap(int T,int n){
	reg ll ans=0;
	switch(T){
		case 1:{
			reg int t=(n+1)>>1;
			a[0]=-1;
			a[n+1]=inf;
			for(reg int i=1;i<=t;++i)
				MinMax(a[i-1]+1,a[n-i+2]-1,&a[i],&a[n-i+1]);
			for(reg int i=1;i<n;++i)
				ans=max(ans,a[i+1]-a[i]);
			break;
		}
		case 2:{
			ll a1,an;
			MinMax(0,inf,&a1,&an);
			reg ll las=a1,t=(an-a1)/(n-1);
			if((an-a1)%(n-1)!=0)
				++t;
			for(reg ll i=a1+1;i<an;i+=t){
				ll l,r;
				MinMax(i,min(i+t-1,an-1),&l,&r);
				if(l!=-1)
					ans=max(ans,l-las),las=r;
			}
			ans=max(ans,an-las);
			break;
		}
	}
	return ans;
}