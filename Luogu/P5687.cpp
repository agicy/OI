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

const int MAXN=3e5+5;
const int MAXM=3e5+5;

int n,m;
int a[MAXN],b[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i)
		b[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	reg int ptr1=2,ptr2=2,h=1,l=1;
	reg ll sum=1ll*(n-1)*(m-1),ans=1ll*a[1]*(m-1)+1ll*b[1]*(n-1);
	while(sum)
		if(a[ptr1]<b[ptr2])
			ans+=1ll*a[ptr1++]*(m-h),++l,sum-=m-h;
		else
			ans+=1ll*b[ptr2++]*(n-l),++h,sum-=n-l;
	printf("%lld\n",ans);
	return 0;
}