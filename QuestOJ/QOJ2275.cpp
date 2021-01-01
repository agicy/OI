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

const int MAXL=1e6+100;

int T[MAXL];

int main(void){
	reg int n=read();
	for(reg int i=1;i<=n;++i)
		++T[read()];
	reg int ans=0;
	for(reg int i=0;i<MAXL;++i){
		if(T[i]>=2)
			T[i+1]+=(T[i]>>1);
		ans+=(T[i]&1);
	}
	printf("%d\n",ans);
	return 0;
}