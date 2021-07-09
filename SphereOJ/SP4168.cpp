#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

const int MAXT=100+5;
const int MAXS=1e7+5;

int t;
ll n[MAXT];
bool vis[MAXS];
int tot,prime[MAXS];
int mu[MAXS];
int Smu[MAXS];

inline void init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(reg int i=1;i<=n;++i)
		Smu[i]=Smu[i-1]+mu[i];
	return;
}

inline ll query(reg ll n){
	reg ll res=0;
	for(reg ll l=1,r;l<=n;l=r+1){
		if(!(n/(l*l)))
			break;
		r=sqrt(n/(n/(l*l)));
		res+=n/(l*l)*(Smu[r]-Smu[l-1]);
	}
	return res;
}

bool ed;

int main(void){
	int t;
	scanf("%d",&t);
	reg ll Max=0;
	for(reg int i=1;i<=t;++i){
		scanf("%lld",&n[i]);
		if(Max<n[i]) Max=n[i];
	}
	init(sqrt(Max));
	for(reg int i=1;i<=t;++i)
		printf("%lld\n",query(n[i]));
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}