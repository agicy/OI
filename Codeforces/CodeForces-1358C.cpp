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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int main(void){
	reg int T=read();
	while(T--){
		reg int x1=read(),y1=read(),x2=read(),y2=read();
		reg ll x=x2-x1+1,y=y2-y1+1;
		printf("%lld\n",(x-1)*(y-1)+1);
	}
	return 0;
}