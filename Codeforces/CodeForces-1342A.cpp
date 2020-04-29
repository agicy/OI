#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int T;
ll x,y,a,b;

int main(void){
	reg int T=read();
	while(T--){
		x=read(),y=read(),a=read(),b=read();
		if(2*a<=b)
			printf("%lld\n",abs(x)*a+abs(y)*a);
		else
			printf("%lld\n",abs(x-y)*a+min(abs(x),abs(y))*b);
	}
	return 0;
}
