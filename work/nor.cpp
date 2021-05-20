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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=3e6+5;

int n;
int l[MAXN];

namespace Subtask1{
	struct Interval{
		int l,r;
		inline Interval(reg int l=0,reg int r=0):l(l),r(r){
			return;
		}
		inline int len(void)const{
			return r-l+1;
		}
	};
	inline Interval cap(const Interval& a,const Interval& b){
		return Interval(max(a.l,b.l),min(a.r,b.r));
	}
	inline void Solve(void){
		reg ll ans=0;
		for(reg int L=1;L<=n;++L)
			for(reg int R=L;R<=n;++R){
				reg int Max=0;
				for(reg int i=1;i<=n;++i)
					Max=max(Max,cap(Interval(L,R),Interval(l[i],i)).len());
				ans+=Max;
			}
		printf("%lld\n",ans);
		return;
	}
}

namespace Subtask2{
	inline ll getSum1(reg int i){
		return 1ll*i*(i+1)/2;
	}
	inline ll getSum1(reg int l,reg int r){
		return getSum1(r)-getSum1(l-1);
	}
	struct Interval{
		int l,r;
		inline Interval(reg int l=0,reg int r=0):l(l),r(r){
			return;
		}
		inline int len(void)const{
			return r-l+1;
		}
	};
	int tot;
	Interval a[MAXN];
	ll f[MAXN];
	inline void Solve(void){
		reg int top=0;
		static int S[MAXN];
		for(reg int i=1;i<=n;++i){
			while(top&&l[S[top]]>=l[i])
				--top;
			S[++top]=i;
		}
		for(reg int i=1;i<=top;++i)
			a[++tot]=Interval(l[S[i]],S[i]);
		top=0;
		for(reg int i=1;i<=tot;++i){
			for(reg int j=a[i-1].r+1;j<=a[i].r;++j){
				reg int len=j-a[i].l+1;
				while(top&&a[S[top]].len()<=len)
					--top;
				reg int k=S[top];
				if(!k)
					f[j]=getSum1(len)+1ll*len*(a[i].l-1);
				else
					f[j]=getSum1(len)+1ll*(j-a[k].r-1)*len+f[a[k].r]-getSum1(j-a[i].l);
			}
			S[++top]=i;
		}
		reg ll ans=0;
		for(reg int i=1;i<=n;++i)
			ans+=f[i];
		printf("%lld\n",ans);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		l[i]=read();
	Subtask2::Solve();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}