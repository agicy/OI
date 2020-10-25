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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int n,m;

int main(void){
	n=read(),m=read();
	if(n==1&&m==0)
		puts("1 2");
	else if(m>n-2||m<0)
		puts("-1");
	else if(!m)
		for(reg int i=1;i<=n;++i)
			printf("%d %d\n",i,i+n);
	else{
		const int Delta=3e5;
		for(reg int i=1;i<=m+1;++i)
			printf("%d %d\n",i*2-1+Delta,i*2+Delta);
		for(reg int i=m+2,l=0,r=(m+1)*2+1;i<=n;++i,--l,++r)
			printf("%d %d\n",Delta+l,Delta+r);
	}
	return 0;
}