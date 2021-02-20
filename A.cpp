#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

ll n;

namespace Subtask1{
	const int MAXN=1e5+5;
	bool vis[MAXN];
	int tot,prime[MAXN];
	int from[MAXN];
	inline void Init(reg int n){
		from[1]=1;
		for(reg int i=2;i<=n;++i){
			if(!vis[i]){
				prime[++tot]=i;
				from[i]=i;
			}
			for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
				vis[i*prime[j]]=true;
				from[i*prime[j]]=prime[j];
				if(!(i%prime[j]))
					break;
			}
		}
		return;
	}
	inline void Solve(void){
		Init(1e5);
		reg ll ans=0;
		for(reg int i=2;i<=n;++i){
			reg int Max=0,Min=64;
			reg int tmp=i;
			while(tmp!=1){
				reg int p=from[tmp];
				reg int cnt=0;
				while(!(tmp%p))
					++cnt,tmp/=p;
				Max=max(Max,cnt),Min=min(Min,cnt);
			}
			ans+=1ll*Max*Min;
		}
		printf("%lld\n",ans);
		return;
	}
}

namespace Subtask2{
	const int MAXN=1e7+5;
	bool vis[MAXN];
	int tot,prime[MAXN];
	int from[MAXN];
	inline void Init(reg int n){
		from[1]=1;
		for(reg int i=2;i<=n;++i){
			if(!vis[i]){
				prime[++tot]=i;
				from[i]=i;
			}
			for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
				vis[i*prime[j]]=true;
				from[i*prime[j]]=prime[j];
				if(!(i%prime[j]))
					break;
			}
		}
		return;
	}
	inline int f(reg int x){
		reg int Max=0,Min=64;
		reg int tmp=x;
		while(tmp!=1){
			reg int p=from[tmp];
			reg int cnt=0;
			while(!(tmp%p))
				++cnt,tmp/=p;
			Max=max(Max,cnt),Min=min(Min,cnt);
		}
		return 1ll*Max*Min;
	}
	const ll Ans[]={175279,172315,171874,171503,171343,171631,171157,171175,171130,171100,171331,171022,171031,170975,170985,171064,170900,170945,170899,170982,171264,170883,170925,170806,170888,170896,170836,170788,170855,170849,170759,170865,170772,170802,170788,170834,170793,170804,170755,170808,170766,171241,170753,170785,170830,170706,170728,170909,170772,170766,170786,170789,170717,170783,170737,170685,170791,170778,170666,170784,170699,170694,170756,170777,170725,170708,170691,170740,170750,170676,170753,170700,170696,170740,170715,170755,170668,170708,170695,170781,170661,170697,170678,171167,170692,170710,170708,170694,170660,170776,170648,170669,170665,170647,170669,170702,170656,170755,170705,170694};
	inline void Solve(void){
		Init(1e7);
		const int X=1e5;
		reg int id=(n-1)/X+1;
		reg ll sum=0;
		for(reg int i=0;i<id-1;++i)
			sum+=Ans[i];
		for(reg int i=(id-1)*X+1;i<=n;++i)
			sum+=f(i);
		printf("%lld\n",sum);
		return;
	}
}

int main(void){
	n=readll();
	if(n<=1e5)
		Subtask1::Solve();
	else if(n<=1e7)
		Subtask2::Solve();
	return 0;
}