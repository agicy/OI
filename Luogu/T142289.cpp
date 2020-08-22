#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=3e5+5;

int n;
int a[MAXN];

namespace Subtask4{
	ll arr[MAXN];
	inline ll gcd(reg ll a,reg ll b){
		return b==0?a:gcd(b,a%b);
	}
	inline ll lcm(reg ll a,reg ll b){
		return a*b/gcd(a,b);
	}
	inline bool check(reg int a,reg int b){
		reg ll x=0ll+a+b+gcd(a,b);
		reg ll y=lcm(a,b);
		return x==y||a==b;
	}
	vector<int> G[MAXN];
	ll sum;
	bitset<MAXN> vis;
	inline void dfs(reg int u){
		sum+=arr[u];
		vis[u]=true;
		for(auto x:G[u])
			dfs(x);
		return;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			arr[i]=a[i];
		sort(arr+1,arr+n+1);
		for(int i=1;i<=n;++i)
			for(reg int j=i+1;j<=n;++j)
				if(check(arr[i],arr[j]))
					G[j].push_back(i);
		ll ans=0;
		for(reg int i=n;i>=1;--i){
			if(!vis[i]){
				sum=0;
				dfs(i);
				ans=max(ans,sum);
			}
		}
		printf("%lld\n",ans);
		return;
	}
}

namespace Subtask7{
	ll arr[MAXN];
	int id2[MAXN],id3[MAXN];
	ll sum;
	bitset<MAXN> vis;
	vector<int> T2[MAXN],T3[MAXN];
	map<int,int> cnt;
	inline void dfs(reg int u){
		vis[u]=true;
		sum+=1ll*arr[u]*cnt[arr[u]];
		for(auto x:T2[id2[u]])
			if(!vis[x])
				dfs(x);
		for(auto x:T3[id3[u]])
			if(!vis[x])
				dfs(x);
		return;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i){
			arr[i]=a[i];
			++cnt[a[i]];
		}
		sort(arr+1,arr+n+1);
		n=unique(arr+1,arr+n+1)-(arr+1);
		ll ans=0;
		vector<int> V;
		for(reg int i=1;i<=n;++i){
			if(arr[i]%2==0)
				V.push_back(arr[i]/2);
			if(arr[i]%3==0)
				V.push_back(arr[i]/3);
		}
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(),V.end()),V.end());
		for(int i=1;i<=n;++i){
			if(arr[i]%2==0){
				reg int x=lower_bound(V.begin(),V.end(),arr[i]/2)-V.begin()+1;
				id3[i]=x;
				T2[x].push_back(i);
			}
			if(arr[i]%3==0){
				reg int x=lower_bound(V.begin(),V.end(),arr[i]/3)-V.begin()+1;
				id2[i]=x;
				T3[x].push_back(i);
			}
		}
		for(reg int i=1;i<=n;++i)
			if(!vis[i]){
				sum=0;
				dfs(i);
				ans=max(ans,sum);
			}
		printf("%lld\n",ans);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	Subtask7::Solve();
	return 0;
}