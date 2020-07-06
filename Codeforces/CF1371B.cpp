#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

ull n,r;

int main(void){
	reg int T=read();
	while(T--){
		n=read(),r=read();
		reg ull ans=0;
		if(n<=r){
			ans=(((n-1ull)*n)>>1ull)+1ull;
		}
		else
			ans=((r+1ull)*r)>>1;
		printf("%llu\n",ans);
	}
	return 0;
}