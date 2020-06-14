#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

int n,x;

int main(void){
	reg int T=read();
	while(T--){
		n=read(),x=read();
		reg int sum=0,l=-1,r;
		for(reg int i=0;i<n;++i){
			static int a;
			a=read();
			if(a%x!=0){
				if(l==-1)
					l=i;
				r=i;
			}
			sum+=a;
		}
		if(sum%x!=0)
			printf("%d\n",n);
		else if(l==-1)
			puts("-1");
		else
			printf("%d\n",n-min(l+1,n-r));
	}
	return 0;
}