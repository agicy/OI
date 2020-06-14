#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 10086
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;

int n;

namespace Basis{
	const int MAXLOG2A=31;
	int p[MAXLOG2A];
	inline int insert(reg int x){
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			if(!((x>>i)&1))
				continue;
			if(!p[i]){
				p[i]=x;
				return true;
			}
			else
				x^=p[i];
		}
		return false;
	}
	inline int queryrnk(reg int x){
		reg int res=0;
		reg int temp=1;
		for(reg int i=0;i<MAXLOG2A;++i)
			if(p[i]){
				if(((x>>i)&1))
					res=(res+temp%MOD)%MOD;
				temp<<=1;
			}
		return res;
	}
}

using namespace Basis;

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

int main(void){
	n=read();
	reg int cnt=0;
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		if(insert(a))
			++cnt;
	}
	printf("%d\n",(queryrnk(read())*pow(2,n-cnt,MOD)%MOD+1)%MOD);
	return 0;
}