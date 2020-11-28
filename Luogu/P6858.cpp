#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int p=998244353;

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

inline int calc(reg int x){
	return ((1ll*x*x+5ll*x+2ll)/2ll)%p;
}

inline int frac(reg int x,reg int y){
	return 1ll*x*fpow(y,p-2)%p;
}

int n,m;

int main(void){
	n=read()%p,m=read();
	if(!m)
		printf("%d\n",(calc(n-1)+1)%p);
	else{
		reg int ans=calc(n);
		for(reg int i=2;i<=m;++i)
			ans=(1ll*frac(n,n+i)*calc(n+i-1)%p+1ll*ans*frac(i,n+i)%p+1)%p;
		printf("%d\n",ans);
	}
	return 0;
}