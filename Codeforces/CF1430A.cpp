#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

int n;

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		if(n==1||n==2||n==4)
			puts("-1");
		else if(n%3==0)
			printf("%d 0 0\n",n/3);
		else if(n%3==1)
			printf("%d 0 1\n",n/3-2);
		else
			printf("%d 1 0\n",n/3-1);
	}
	return 0;
}