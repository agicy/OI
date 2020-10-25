#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+1;
const int p=1e9+7;

int fac[MAXN],invfac[MAXN];

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

inline int A(reg int n,reg int m){
	if(m<0||m>n)
		return 0;
	else
		return mul(fac[n],invfac[n-m]);
}

inline int C(reg int n,reg int m){
	if(m<0||m>n)
		return 0;
	else
		return mul(fac[n],mul(invfac[m],invfac[n-m]));
}

int main(void){
	fac[0]=1;
	for(reg int i=1;i<MAXN;++i)
		fac[i]=mul(fac[i-1],i);
	invfac[MAXN-1]=fpow(fac[MAXN-1],p-2);
	for(reg int i=MAXN-2;i>=0;--i)
		invfac[i]=mul(invfac[i+1],i+1);
	reg int n=read(),x=read(),pos=read();
	reg int cntl=0,cntg=0;
	reg int l=0,r=n,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(pos<mid){
			++cntg;
			r=mid;
		}
		else if(pos==mid)
			l=mid+1;
		else{
			++cntl;
			l=mid+1;
		}
	}
	printf("%d\n",mul(mul(mul(A(n-x,cntg),A(x-1,cntl)),mul(A(n-x-cntg,n-x-cntg),A(x-1-cntl,x-1-cntl))),C(n-cntg-cntl-1,n-x-cntg)));
	return 0;
}