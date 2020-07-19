#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
const int MOD=1e9+7;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=(10ll*res+ch-'0')%(MOD-1),ch=getchar();
	return res;
}

int n;

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int main(void){
	n=read();
	reg int ans=(485071604ll*pow(940286408,(n-1+MOD-1)%(MOD-1),MOD)%MOD+514928404ll*pow(59713601,(n-1+MOD-1)%(MOD-1),MOD)%MOD)%MOD;
	printf("%d\n",ans);
	return 0;
}