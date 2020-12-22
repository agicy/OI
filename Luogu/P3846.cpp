#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

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

map<int,int> M;

signed main(void){
	reg int p=read(),y=read(),z=read();
	reg int m=ceil(sqrt(p));
	if(y%p==0&&z){
		puts("no solution");
		return 0;
	}
	M.clear();
	int x=z%p,f=pow(y,m,p);
	M[x]=0;
	for(reg int i=1;i<=m;++i){
		x=(x*y)%p;
		M[x]=i;
	}
	x=1;
	reg bool flag=true;
	for(reg int i=1;i<=m;++i){
		x=1ll*x*f%p;
		if(M[x]){
			reg int ans=(i*m-M[x])%p;
			printf("%lld\n",(ans+p)%p);
			flag=false;
			break;
		}
	}
	if(flag)
		puts("no solution");
	return 0;
}