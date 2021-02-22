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

const int inf=0x3f3f3f3f;

int main(void){
	reg int t=read();
	while(t--){
		reg int n=read();
		reg int Min=inf,cnt=0;
		for(reg int i=1;i<=n;++i){
			reg int x=read();
			if(x<Min)
				Min=x,cnt=1;
			else if(x==Min)
				++cnt;
		}
		printf("%d\n",n-cnt);
	}
	return 0;
}