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

inline ll readBinary(void){
	reg ll res=0;
	reg char ch=getchar();
	while(ch!='O'&&ch!='X')ch=getchar();
	while(ch=='O'||ch=='X')res=(res<<1)|(ch=='X'),ch=getchar();
	return res;
}

int n,m;

namespace Basis{
	const int MAXSIZE=50+1;
	ll unit[MAXSIZE];
	inline bool insert(reg ll x){
		for(reg int i=MAXSIZE-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					break;
				}
				x^=unit[i];
			}
		return x;
	}
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

int main(void){
	n=read(),m=read();
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		static ll x;
		x=readBinary();
		if(Basis::insert(x))
			++tot;
	}
	printf("%d\n",pow(2,tot,2008));
	return 0;
}