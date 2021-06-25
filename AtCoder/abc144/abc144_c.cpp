#include<cstdio>
#include<cmath>
#define reg register
typedef long long ll;
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

ll n;

int main(void){
	reg ll i;
	n=read();
	for(i=ceil(sqrt(n));i>=1;--i)
		if(n%i==0){
			printf("%lld\n",i-1+(n/i)-1);
			break;
		}
	return 0;
}