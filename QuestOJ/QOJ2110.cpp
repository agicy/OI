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

const int p=1e9+7;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x){
	return fpow(x,p-2);
}

inline int frac(reg int x){
	reg int res=1;
	for(reg int i=2;i<=x;++i)
		res=1ll*res*i%p;
	return res;
}

int n,m;

int main(void){
	n=read(),m=read(),read();
	reg int ans=inv(m+1);
	for(reg int i=n+1;i<=n+m+1;++i)
		ans=1ll*ans*i%p;
	ans=(ans-frac(m)+p)%p;
	printf("%d\n",ans);
	return 0;
}