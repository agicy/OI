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

inline bool isPrime(reg int x){
	if(x<=1)
		return false;
	for(reg int i=2;1ll*i*i<=x;++i)
		if(!(x%i))
			return false;
	return true;
}

inline int calc(reg int x,reg int k){
	if(!isPrime(k))
		return 0;
	reg int sum=x/k;
	for(reg int i=2;i<=x/k&&i<k;++i)
		sum-=calc(x/k,i);
	return sum;
}

int main(void){
	reg int l=read(),r=read(),k=read();
	printf("%d\n",calc(r,k)-calc(l-1,k));
	return 0;
}