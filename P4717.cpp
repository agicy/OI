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

namespace Poly{
	const int p=998244353;
	typedef vector<int> poly;
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
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline void FWT_or(poly& a,reg int flag){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					if(flag==1)
						a[i+j+k]=add(a[i+j+k],a[j+k]);
					else
						a[i+j+k]=sub(a[i+j+k],a[j+k]);
		return;
	}
	inline void FWT_and(poly& a,reg int flag){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					if(flag==1)
						a[j+k]=add(a[j+k],a[i+j+k]);
					else
						a[j+k]=sub(a[j+k],a[i+j+k]);
		return;
	}
	inline void FWT_xor(poly& a,reg int flag){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k){
					reg int x=a[j+k],y=a[i+j+k];
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
		if(flag==-1){
			reg int inv=fpow(n,p-2);
			for(reg int i=0;i<n;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
}

using namespace Poly;

int n;
poly a,b;
poly tmpa,tmpb;

int main(void){
	n=read();
	a.resize(1<<n),b.resize(1<<n);
	for(reg int i=0;i<(1<<n);++i)
		a[i]=read();
	for(reg int i=0;i<(1<<n);++i)
		b[i]=read();
	tmpa=a,tmpb=b;
	FWT_or(tmpa,1),FWT_or(tmpb,1);
	for(reg int i=0;i<(1<<n);++i)
		tmpa[i]=1ll*tmpa[i]*tmpb[i]%p;
	FWT_or(tmpa,-1);
	for(reg int i=0;i<(1<<n);++i)
		printf("%d%c",tmpa[i],i==(1<<n)-1?'\n':' ');
	tmpa=a,tmpb=b;
	FWT_and(tmpa,1),FWT_and(tmpb,1);
	for(reg int i=0;i<(1<<n);++i)
		tmpa[i]=1ll*tmpa[i]*tmpb[i]%p;
	FWT_and(tmpa,-1);
	for(reg int i=0;i<(1<<n);++i)
		printf("%d%c",tmpa[i],i==(1<<n)-1?'\n':' ');
	tmpa=a,tmpb=b;
	FWT_xor(tmpa,1),FWT_xor(tmpb,1);
	for(reg int i=0;i<(1<<n);++i)
		tmpa[i]=1ll*tmpa[i]*tmpb[i]%p;
	FWT_xor(tmpa,-1);
	for(reg int i=0;i<(1<<n);++i)
		printf("%d%c",tmpa[i],i==(1<<n)-1?'\n':' ');
	return 0;
}