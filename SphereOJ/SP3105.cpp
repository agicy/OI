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

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline int fpow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline void exgcd(reg int a,reg int b,reg int &x,reg int &y){
	if(!b){
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return;
}

inline int inv(reg int x,reg int p){
	int res,tmp;
	exgcd(x,p,res,tmp);
	return (res%p+p)%p;
}


inline int BSGS(reg int a,reg int b,reg int p){
	map<int,int> M;
	reg int m=ceil(sqrt(p));
	for(reg int i=1;i<=m;++i){
		b=1ll*b*a%p;
		M[b]=i;
	}
	reg int tmp=fpow(a,m,p);
	b=1;
	for(reg int i=1;i<=m;++i){
		b=1ll*b*tmp%p;
		if(M.count(b))
			return i*m-M[b];
	}
	return -1;
}

inline int exBSGS(reg int a,reg int b,reg int p){
	if(b==1||p==1)
		return 0;
	reg int g;
	reg int k=0,pod=1;
	while((g=gcd(a,p))>1){
		if(b%g)
			return -1;
		++k;
		b/=g,p/=g,pod=1ll*pod*(a/g)%p;
		if(pod==b)
			return k;
	}
	reg int res=BSGS(a,1ll*b*inv(pod,p)%p,p);
	if(res==-1)
		return -1;
	else
		return res+k;
}

int main(void){
	reg int a,p,b;
	while(a=read(),p=read(),b=read(),a||p||b){
		reg int res=exBSGS(a,b,p);
		if(res==-1)
			puts("No Solution");
		else
			printf("%d\n",res);
	}
	return 0;
}