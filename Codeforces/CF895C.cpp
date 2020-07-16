#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXCNT=19+1;

int n;

const int prime[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};

namespace Basis{
	int unit[MAXCNT];
	inline void insert(reg int x){
		for(reg int i=MAXCNT-1;i>=0;--i){
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					break;
				}
				x^=unit[i];
			}
		}
	}
}

inline int pow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;
		exp>>=1;
	}
	return res;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		reg int tmp=0;
		for(reg int j=1;j<=19;++j){
			if(a%prime[j]==0){
				reg int cnt=0;
				while(a%prime[j]==0){
					a/=prime[j];
					cnt^=1;
				}
				if(cnt)
					tmp|=(1<<j);
			} 
		}
		Basis::insert(tmp);
	}
	for(reg int i=MAXCNT-1;i>=0;--i)
		if(Basis::unit[i])
			--n;
	printf("%lld\n",(pow(2,n)-1ll+MOD)%MOD);
	return 0;
}
