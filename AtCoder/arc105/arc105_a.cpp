#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+ch-'0',ch=getchar();
	return res;
}

int a[4];

int main(void){
	reg int sum=0;
	for(reg int i=0;i<4;++i){
		a[i]=read();
		sum+=a[i];
	}
	for(reg int S=1;S<(1<<4);++S){
		reg int s=0;
		for(reg int i=0;i<4;++i)
			if((S>>i)&1)
				s+=a[i];
		if(s==sum-s){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}