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

const int p=998244353;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

int n;

int main(void){
	n=read();
	reg int sum=0,ans=1;
	for(reg int i=1;i<=n;++i){
		static int d;
		d=read();
		sum=add(sum,d);
		ans=mul(ans,d);
	}
	sum=add(sum,p-n);
	for(reg int i=0;i<n-2;++i)
		ans=mul(ans,sum-i);
	printf("%d\n",ans);
	return 0;
}