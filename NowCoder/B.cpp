#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

bool flag;

inline int readwithflag(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9'){
		res=10*res+ch-'0';
		if(res>=66666)
			flag=true;
		ch=getchar();
	}
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

const int p=199999;

inline int sqr(reg int x){
	return 1ll*x*x%p;
}

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

const int inv2=pow(2,p-2,p);
const int inv6=pow(6,p-2,p);

int ans[1048576];

int main(void){
	reg int T=read();
	ans[0]=1;
	for(reg int i=1;i<=66666;++i)
		ans[i]=1ll*ans[i-1]*i%p*inv2%p*add(sqr(1ll*i*add(i,1)%p*inv2%p),1ll*i*add(i,1)%p*add(2ll*i%p,1)%p*inv6%p)%p;
	while(T--){
		flag=false;
		reg int n=readwithflag();
		if(flag)
			puts("0");
		else
			printf("%d\n",ans[n]);
	}
	return 0;
}