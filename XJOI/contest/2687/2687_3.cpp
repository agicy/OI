#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int S=1e6;

bool vis[S+1];
int tot,prime[S+1];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

inline bool isPrime(reg ll x){
	if(x<=S)
		return !vis[x];
	else{
		for(reg int i=1;i<=tot&&1ll*prime[i]*prime[i]<=x;++i)
			if(!(x%prime[i]))
				return false;
		return true;
	}
}

int cnt;
ll Max;
vector<ll> V;

inline void dfs(reg ll y,reg int p,reg ll pod){
	if(y==1){
		++cnt;
		Max=max(Max,pod);
		return;
	}
	if(y+1>V[p]&&isPrime(y+1))
		++cnt,Max=max(Max,pod*(y+1));
	for(reg int i=p+1,siz=V.size();i<siz&&1ll*(V[i]-1)*(V[i]-1)<=y;++i)
		if(!(y%(V[i]-1))){
			reg ll ny=y/(V[i]-1),npod=pod*V[i];
			dfs(ny,i,npod);
			while(!(ny%V[i]))
				ny/=V[i],npod*=V[i],dfs(ny,i,npod);
		}
	return;
}

bool ed;

int main(void){
	Init(S);
	int t;
	scanf("%d",&t);
	while(t--){
		ll y;
		scanf("%lld",&y);
		V.clear();
		V.push_back(2);
		for(reg int i=2;i<=tot;++i)
			if(!(y%(prime[i]-1)))
				V.push_back(prime[i]);
		cnt=Max=0;
		dfs(y,0,1),dfs(y,0,2);
		reg ll bas=2;
		while(!(y&1))
			y>>=1,bas<<=1,dfs(y,0,bas);
		printf("%d %lld\n",cnt,Max);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}