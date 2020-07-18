#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 10007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

int n,m;

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
	n=read(),m=read();
	reg int nm=n*m;
	reg int res=1;
	reg int a=nm,b=n-1;
	for(reg int i=a,j=b;i>=a-b+1;--i,--j)
		res=1ll*res*i%MOD*pow(j,MOD-2)%MOD;
	res=1ll*res*pow(n,MOD-2)%MOD;
	printf("%d\n",res);
	return 0;
}
