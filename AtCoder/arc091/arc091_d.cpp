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

inline int sg(reg int a,reg int k){
	if(a<k)
		return 0;
	else if(!(a%k))
		return a/k;
	else{
		reg int x=a/k;
		reg int cnt=(a-x*k)/(x+1);
		reg int nex=a-cnt*(x+1);
		if(!(nex%k))
			return nex/k;
		else
			return sg(nex-x-1,k);
	}
}

int n;

int main(void){
	n=read();
	reg int res=0;
	for(reg int i=1;i<=n;++i){
		static int a,k;
		a=read(),k=read();
		res^=sg(a,k);
	}
	if(res)
		puts("Takahashi");
	else
		puts("Aoki");
	return 0;
}