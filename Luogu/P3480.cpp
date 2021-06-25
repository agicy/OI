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

const int MAXN=1e3+5;

int n;
int a[MAXN],c[MAXN];

int main(void){
	reg int u=read();
	while(u--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read(),c[i]=a[i]-a[i-1];
		reg int res=0;
		for(reg int i=1;i<=n;++i)
			if(!((n^i)&1))
				res^=c[i];
		puts(res?"TAK":"NIE");
	}
	return 0;
}