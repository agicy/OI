#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int p=998244353;
const int MAXN=500+5;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int pow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

int n,m,p1,p2,p3;
ll k;
int x[MAXN],ans[MAXN];

inline void mul(reg int a[],reg int b[],reg int res[]){
	for(reg int i=0;i<n;++i)
		res[i]=0;
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			res[(i+j)%n]=add(res[(i+j)%n],mul(a[i],b[j]));
	return;
}

int a[MAXN],pro[MAXN],tmp[MAXN];

int main(void){
	scanf("%d%lld%d%d%d",&n,&k,&p1,&p2,&p3);
	reg int invs=pow(p1+p2+p3,p-2);
	p1=mul(p1,invs),p2=mul(p2,invs),p3=mul(p3,invs);
	a[n-1]=p2,a[0]=p3,a[1]=p1;
	pro[0]=1;
	while(k){
		if(k&1){
			mul(pro,a,tmp);
			memcpy(pro,tmp,sizeof(tmp));
		}
		mul(a,a,tmp);
		memcpy(a,tmp,sizeof(tmp));
		k>>=1;
	}
	for(reg int i=0;i<n;++i)
		scanf("%d",&x[i]);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			ans[j]=add(ans[j],mul(pro[(j-i+n)%n],x[i]));
	for(reg int i=0;i<n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}