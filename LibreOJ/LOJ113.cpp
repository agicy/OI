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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXLOG2S=51;

namespace Basis{
	ll unit[MAXLOG2S];
	inline void insert(reg ll x){
		for(reg int i=MAXLOG2S-1;i>=0;--i)
			if((x>>i)&1){
				if(unit[i])
					x^=unit[i];
				else{
					unit[i]=x;
					break;
				}
			}
		return;
	}
	inline ll query(void){
		reg ll res=0;
		for(reg int i=MAXLOG2S-1;i>=0;--i)
			if((res^unit[i])>res)
				res^=unit[i];
		return res;
	}
}

int main(void){
	reg int n=read();
	while(n--)
		Basis::insert(readll());
	printf("%lld\n",Basis::query());
	return 0;
}