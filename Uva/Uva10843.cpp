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

const int mod=2000000011;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int main(void){
	reg int t=read();
	for(reg int Case=1;Case<=t;++Case){
		reg int n=read();
		switch(n){
			case 1:{
				printf("Case #%d: 1\n",Case);
				break;
			}
			case 2:{
				printf("Case #%d: 1\n",Case);
				break;
			}
			default:{
				printf("Case #%d: %d\n",Case,fpow(n,n-2));
				break;
			}
		}
	}
	return 0;
}