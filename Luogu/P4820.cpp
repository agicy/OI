#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define eps 1e-6
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

ll n,m;

int main(void){
	n=read(),m=read();
	reg double f=0;
	if(n>=1e7)
		f=(log(n)+0.5772156649)*0.5;
	else
		for(reg int i=1;i<=n;++i)
			f+=0.5/i;
	printf("%.0f\n",floor(f*m-eps));
	return 0;
}
