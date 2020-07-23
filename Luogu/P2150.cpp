#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;

int n;
ll p;

const int prime[]={2,3,5,7,11,13,17,19};

const int MAXSIZE=8;

struct Node{
	int val,S,Max;
	inline Node(void){
		val=S=Max=0;
		return;
	}
	inline Node(reg int v){
		val=v,S=0;
		for(reg int i=0;i<MAXSIZE;++i)
			if(v%prime[i]==0){
				S|=(1<<i);
				while(v%prime[i]==0)
					v/=prime[i];
			}
		Max=(v>1)?(v):(-1);
		return;
	}
	inline bool operator<(const Node& a)const{
		return Max<a.Max;
	}
};

Node a[MAXN];
ll f1[1<<MAXSIZE][1<<MAXSIZE],f2[1<<MAXSIZE][1<<MAXSIZE];
ll dp[1<<MAXSIZE][1<<MAXSIZE];

int main(void){
	scanf("%d%lld",&n,&p);
	for(reg int i=1;i<n;++i)
		a[i]=Node(i+1);
	sort(a+1,a+n);
	reg int U=(1<<8)-1;
	dp[0][0]=1;
	for(reg int i=1;i<n;++i){
		if(i==1||a[i].Max!=a[i-1].Max||a[i].Max==-1){
			memcpy(f1,dp,sizeof(dp));
			memcpy(f2,dp,sizeof(dp));
		}
		for(reg int S1=U;S1>=0;--S1)
			for(reg int S2=U;S2>=0;--S2)
				if(!(S1&S2)){
					if(!(S1&a[i].S))
						f2[S1][S2|a[i].S]=(f2[S1][S2|a[i].S]+f2[S1][S2])%p;
					if(!(S2&a[i].S))
						f1[S1|a[i].S][S2]=(f1[S1|a[i].S][S2]+f1[S1][S2])%p;
				}
		if(i==n-1||a[i].Max!=a[i+1].Max||a[i].Max==-1){
			for(reg int S1=0;S1<=U;++S1)
				for(reg int S2=0;S2<=U;++S2)
					if(!(S1&S2))
						dp[S1][S2]=((f1[S1][S2]+f2[S1][S2])%p-dp[S1][S2]+p)%p;
		}
	}
	reg ll ans=0;
	for(reg int S1=U;S1>=0;--S1)
		for(reg int S2=U;S2>=0;--S2)
			if(!(S1&S2))
				ans=(ans+dp[S1][S2])%p;
	printf("%lld\n",ans);
	return 0;
}
