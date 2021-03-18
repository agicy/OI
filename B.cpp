#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=1e9+7;

int n,k,p;

namespace Subtask1{
	const int MAXN=8+5;
	bool vis[MAXN];
	int per[MAXN];
	int ans;
	inline void check(void){
		map<set<int>,bool> M;
		reg int cnt=0;
		for(reg int i=1;i+k-1<=n;++i){
			set<int> V;
			for(reg int j=i;j<=i+k-1;++j)
				V.insert(per[j]);
			if(!M[V])
				++cnt,M[V]=true;
			for(reg int j=i+k;j<=n;++j){
				V.insert(per[j]);
				while(V.size()>k)
					V.erase(--V.end());
				if(!M[V])
					++cnt,M[V]=true;
			}
		}
		if(cnt==p)
			++ans;
		return;
	}
	inline void dfs(reg int dep){
		if(dep==n+1){
			check();
			return;
		}
		for(reg int i=1;i<=n;++i)
			if(!vis[i]){
				vis[i]=true;
				per[dep]=i;
				dfs(dep+1);
				vis[i]=false;
			}
		return;
	}
	inline void Solve(void){
		dfs(1);
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask5{
	inline void Solve(void){
		reg int res=1;
		for(reg int i=1;i<=n;++i)
			res=1ll*res*i%mod;
		printf("%d\n",res);
		return;
	}
}

namespace Subtask6{
	inline void Solve(void){
		reg int res=1;
		for(reg int i=1;i<=n;++i)
			res=1ll*res*i%mod;
		printf("%d\n",res);
		return;
	}
}

namespace Subtask7{
	inline void Solve(void){
		if(k==1){
			reg int res=1;
			for(reg int i=1;i<=n;++i)
				res=1ll*res*i%mod;
			printf("%d\n",res);
		}
		else{
			reg int res=1;
			for(reg int i=1;i<=k;++i)
				res=1ll*res*i%mod;
			for(reg int i=1;i<=n-k;++i)
				res=2ll*res%mod;
			printf("%d\n",res);
		}
		return;
	}
}

namespace Subtask8{
	inline void Solve(void){
		puts("0");
		return;
	}
}

int main(void){
	scanf("%d%d%d",&n,&k,&p);
	reg int cnt=0;
	for(reg int i=1;i+k-1<=n;++i)
		cnt+=(n-(i+k-1)+1);
	//printf("cnt=%d\n",cnt);
	if(n<=8)
		//puts("S1"),
		Subtask1::Solve();
	else 
	if(k==1&&p==n)
		//puts("S5"),
		Subtask5::Solve();
	else 
	if(k==n&&p==1)
		//puts("S6"),
		Subtask6::Solve();
	else 
	if(k+p==n+1)
		//puts("S7"),
		Subtask7::Solve();
	else
	if(p>1ll*n*(n+1)/2||p>cnt)
		//puts("S8"),
		Subtask8::Solve();
	else
		puts("0");
	return 0;
}