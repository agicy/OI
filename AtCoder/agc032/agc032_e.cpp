#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

int n,m;
int a[MAXN<<1];

inline int check(reg int mid){
	reg int Max=0;
	for(reg int i=mid<<1|1,j=n<<1;i<j;++i,--j){
		if(a[i]+a[j]<m)
			return -1;
		Max=max(Max,a[i]+a[j]-m);
	}
	for(reg int i=1,j=mid<<1;i<j;++i,--j)
		Max=max(Max,a[i]+a[j]);
	return Max;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=(n<<1);++i)
		a[i]=read();
	sort(a+1,a+(n<<1)+1);
	reg int __l=0,__r=n,__mid;
	while(__l<__r){
		__mid=(__l+__r)>>1;
		if(check(__mid)>=0)
			__r=__mid;
		else
			__l=__mid+1;
	}
	printf("%d\n",check(__l));
	return 0;
}