#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int mod=998244353;
const int inv2=(mod+1)/2;
const int inv6=(mod+1)/6;

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
		x=1ll*x*x%mod,exp>>=1;
	}
	return res;
}

inline int getSum0(reg int x){
	return x;
}
inline int getSum0(reg int l,reg int r){
	return sub(getSum0(r),getSum0(l-1));
}

inline int getSum1(reg int x){
	return 1ll*x*(x+1)%mod*inv2%mod;
}

inline int getSum1(reg int l,reg int r){
	return sub(getSum1(r),getSum1(l-1));
}

inline int getSum2(reg int x){
	return 1ll*x*(x+1)%mod*(2ll*x+1)%mod*inv6%mod;
}

inline int getSum2(reg int l,reg int r){
	return sub(getSum2(r),getSum2(l-1));
}

int n;

bool ed;

int main(void){
	scanf("%d",&n);
	reg int ans=0;
	for(reg int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans=add(ans,1ll*((n/l)%mod)*add(5ll*getSum0(l,r)%mod,add(3ll*getSum1(l,r)%mod,2ll*getSum2(l,r)%mod))%mod);
	}
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}