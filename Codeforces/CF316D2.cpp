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

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n,cnt1,cnt2;
int f0,f1,f2;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		if(read()-1)
			++cnt2;
		else
			++cnt1;
	f0=f1=f2=1;
	for(reg int i=2;i<=cnt1;++i)
		f2=add(f1,1ll*f0*(i-1)%mod),f0=f1,f1=f2;
	reg int ans=f2;
	for(reg int i=1;i<=cnt2;++i)
		ans=1ll*ans*(n-i+1)%mod;
	printf("%d\n",ans);
	return 0;
}