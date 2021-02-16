#include <bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,K,T;
int x[MAXN];
ll a[MAXN];

inline bool check(reg int mid){
	for(reg int i=1;i<=n;++i)
		a[i]=x[i]-2ll*T*mid*i;
	if(a[1]<a[n])
		return false;
	reg int ql=K,qr=K;
	for(reg int i=K-1;i>=1;--i)
		if(a[i]>=a[ql])
			ql=i;
	for(reg int i=K+1;i<=n;++i)
		if(a[i]<=a[qr])
			qr=i;
	reg int l=K,r=K;
	while(l!=ql||r!=qr){
		reg bool flag=false;
		reg int L=l,R=r;
		while(L>ql&&a[L-1]>=a[r])
			if(a[--L]>=a[l])
				break;
		if(L<l&&a[L]>=a[l])
			flag=true,l=L;
		while(R<qr&&a[R+1]<=a[l])
			if(a[++R]<=a[r])
				break;
		if(R>r&&a[R]<=a[r])
			flag=true,r=R;
		if(!flag)
			return false;
	}
	l=1,r=n;
	while(l!=ql||r!=qr){
		reg bool flag=false;
		reg int L=l,R=r;
		while(L<ql&&a[L+1]>=a[r])
			if(a[++L]>=a[l])
				break;
		if(L>l&&a[L]>=a[l])
			flag=true,l=L;
		while(R>qr&&a[R-1]<=a[l])
			if(a[--R]<=a[r])
				break;
		if(R<r&&a[R]<=a[r])
			flag=true,r=R;
		if(!flag)
			return false;
	}
	return true;
}

int main(void){
	n=read(),K=read(),T=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read();
	reg int l=0,r=1e9,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}