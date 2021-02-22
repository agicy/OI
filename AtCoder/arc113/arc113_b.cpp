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

int main(void){
	reg int a=read(),b=read(),c=read();
	const int mod=4;
	if((b&3)==2)
		if(c==1)
			b=2;
		else
			b=mod;
	else{
		if(!(c&1))
			b=1ll*b*b%mod;
		else
			b%=mod;
		if(!b)
			b=mod;
	}
	a%=10;
	reg int ans=1;
	for(reg int i=1;i<=b;++i)
		ans=1ll*ans*a%10;
	printf("%d\n",ans);
	return 0;
}