#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int w,x,y,z;

namespace Subtask1{
	inline ll binom(reg ll n,reg ll m){
		reg ll res=1;
		for(reg int i=1;i<=m;++i)
			res=res*(n-i+1);
		for(reg int i=1;i<=m;++i)
			res=res/i;
		return res;
	}
	inline void Solve(void){
		reg ll val1=binom(w,x),val2=binom(y,z);
		if(val1>val2)
			puts("1");
		else if(val1==val2)
			puts("2");
		else
			puts("0");
		return;
	}
}

namespace Subtask2{
	inline int getCnt(reg int x,reg int p){
		reg int res=0;
		while(x)
			res+=x/p,x/=p;
		return res;
	}
	const int MAXS=1e3+5;
	bool init_flag;
	bool vis[MAXS];
	int tot,prime[MAXS];
	inline void init(reg int n=1e3){
		if(init_flag)
			return;
		for(reg int i=2;i<=n;++i){
			if(!vis[i])
				prime[++tot]=i;
			for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
				vis[i*prime[j]]=true;
				if(!(i%prime[j]))
					break;
			}
		}
		init_flag=true;
		return;
	}
	inline bool check(void){
		for(reg int i=1;i<=tot;++i){
			reg int cnt1=getCnt(w,prime[i])-getCnt(x,prime[i])-getCnt(w-x,prime[i]);
			reg int cnt2=getCnt(y,prime[i])-getCnt(z,prime[i])-getCnt(y-z,prime[i]);
			if(cnt1!=cnt2)
				return false;
		}
		return true;
	}
	inline double lgbinom(reg int n,reg int m){
		reg double res=0;
		for(reg int i=1;i<=m;++i)
			res+=log(n-i+1);
		for(reg int i=1;i<=m;++i)
			res-=log(i);
		return res;
	}
	inline void Solve(void){
		init();
		reg bool f=check();
		if(f)
			puts("2");
		else{
			reg double val1=lgbinom(w,x),val2=lgbinom(y,z);
			if(val1>val2)
				puts("1");
			else
				puts("0");
		}
		return;
	}
}

namespace Subtask3{
	const double pi=acos(-1.0);
	inline double getSum(reg int n){
		return n*log(n)-n+0.5*log(2*pi*n);
	}
	inline void Solve(void){
		x=min(x,w-x),z=min(z,y-z);
		if((!x&&!z)||(w==y&&x==z))
			puts("2");
		else if(w==y){
			if(x>z)
				puts("1");
			else
				puts("0");
		}
		else if(x==z){
			if(w>y)
				puts("1");
			else
				puts("0");
		}
		else{
			reg double val1=getSum(w)-(getSum(x)+getSum(w-x));
			reg double val2=getSum(y)-(getSum(z)+getSum(y-z));
			if(val1>val2)
				puts("1");
			else
				puts("0");
		}
		return;
	}
}

int main(void){
	reg int t=100;
	while(t--){
		scanf("%d%d%d%d",&w,&x,&y,&z);
		if(w<=20&&y<=20)
			fputs("S1\n",stderr),Subtask1::Solve();
		else if(w<=1e3&&y<=1e3)
			fputs("S2\n",stderr),Subtask2::Solve();
		else
			fputs("S3\n",stderr),Subtask3::Solve();
	}
	return 0;
}