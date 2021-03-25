#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int n,m;

namespace Subtask1{
	inline void Solve(void){
		reg int cnt=0,sum=0;
		for(reg int x1=0;x1<n;++x1)
			for(reg int y1=0;y1<m;++y1)
		for(reg int x2=0;x2<n;++x2)
			for(reg int y2=0;y2<m;++y2)
		for(reg int x3=0;x3<n;++x3)
			for(reg int y3=0;y3<m;++y3){
				reg int S=(x1*y2+x2*y3+x3*y1)-(x1*y3+x2*y1+x3*y2);
				if(S>0){
					++cnt;
					sum+=gcd(abs(x1-x2),abs(y1-y2))+gcd(abs(x2-x3),abs(y2-y3))+gcd(abs(x3-x1),abs(y3-y1));
				}
			}
		reg int ans=1ll*sum*fpow(cnt,mod-2)%mod;
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=read(),m=read();
	Subtask1::Solve();
	return 0;
}