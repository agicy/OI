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

int n;

inline int getOdd(reg int l,reg int r){
	reg int len=r-l+1;
	if((l&1)+(r&1)==2)
		return (len>>1)+1;
	else
		return len>>1;
}

inline int getEven(reg int l,reg int r){
	reg int len=r-l+1;
	if((l&1)+(r&1))
		return len>>1;
	else
		return (len>>1)+1;
}

int main(void){
	n=read();
	printf("%d\n",getEven(n+1,2*n)+getOdd((n+2)/3,n));
	return 0;
}