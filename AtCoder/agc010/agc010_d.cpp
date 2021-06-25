#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

const int MAXN=1e5+5;

int n;
int a[MAXN];

inline bool solve(void){
	reg bool sum=false;
	for(reg int i=1;i<=n;++i)
		sum^=(a[i]-1)&1;
	if(sum)
		return true;
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		cnt+=a[i]&1;
	if(cnt>1)
		return false;
	for(reg int i=1;i<=n;++i)
		if(a[i]&1){
			if(a[i]==1)
				return false;
			--a[i];
		}
	reg int d=0;
	for(reg int i=1;i<=n;++i)
		d=gcd(d,a[i]);
	for(reg int i=1;i<=n;++i)
		a[i]/=d;
	return !solve();
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	puts(solve()?"First":"Second");
	return 0;
}