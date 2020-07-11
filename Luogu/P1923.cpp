#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=5000000+5;

int n,K;
int a[MAXN];

int main(void){
	n=read(),K=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	nth_element(a,a+K,a+n);
	printf("%d\n",a[K]);
	return 0;
}
