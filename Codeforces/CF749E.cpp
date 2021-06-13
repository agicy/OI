#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	pair<int,ll> unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,const pair<int,ll>& val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i].first+=val.first,unit[i].second+=val.second;
		return;
	}
	inline pair<int,ll> query(reg int id){
		pair<int,ll> res(0,0);
		for(reg int i=id;i;i^=lowbit(i))
			res.first+=unit[i].first,res.second+=unit[i].second;
		return res;
	}
}

inline double getSum1(reg double x){
	return 0.5*x*(x+1);
}

inline double getSum2(reg double x){
	return x*(x+1)*(2*x+1)/6.0;
}

inline double getSum3(reg double x){
	return 0.25*x*x*(x+1)*(x+1);
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg double ans1=(getSum3(n)-(2.0*n+1)*getSum2(n)+1.0*n*(n+1)*getSum1(n))/(2.0*n*(n+1));
	reg double ans2=0;
	BIT::Init(n);
	for(int i=n;i>=1;--i){
		pair<int,ll> p=BIT::query(a[i]-1);
		ans2+=p.first*(1.0-2.0*i/n)+2.0*i*p.second/(1.0*n*(n+1));
		BIT::update(a[i],make_pair(1,i));
	}
	printf("%.30lf\n",ans1+ans2);
	return 0;
}