#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e6+5;

int n;
ll k;
int a[MAXN],b[MAXN];

int main(void){
	n=read(),k=readll();
	reg ll sum1=0,sum2=0;
	for(reg int i=1;i<=n;++i)
		sum1+=i,sum2+=max(n-i+1,i);
	if(k<sum1)
		puts("-1");
	else if(k>=sum2){
		printf("%lld\n",sum2);
		for(reg int i=1;i<=n;++i)
			printf("%d%c",i,i==n?'\n':' ');
		for(reg int i=1;i<=n;++i)
			printf("%d%c",n-i+1,i==n?'\n':' ');
	}
	else{
		for(reg int i=1;i<=n;++i)
			a[i]=i;
		for(reg int i=1;i<=n;++i)
			b[i]=n-i+1;
		reg ll sum=sum1;
		reg int l=1,r=n;
		for(reg int i=1;i<=n;++i)
			if(a[i]<=r&&sum+r-a[i]<=k){
				sum+=r-a[i];
				b[i]=r--;
			}
			else
				b[i]=l++;
		printf("%lld\n",k);
		for(reg int i=1;i<=n;++i)
			printf("%d%c",a[i],i==n?'\n':' ');
		for(reg int i=1;i<=n;++i)
			printf("%d%c",b[i],i==n?'\n':' ');
	}
	return 0;
}