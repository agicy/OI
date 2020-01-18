#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

#define mul(a,b,mod) ( (a) * (b) % (mod) )

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

inline bool Miller_Rabin(reg ll n){
	if(n<3)
		return n==2;
	const int TEST_TIMES=5;
	reg ll u=n-1,t=0;
	while((u&1)==0)
		++t,u>>=1;
	for(reg int i=1;i<=TEST_TIMES;++i){
		reg ll x=rand()%(n-2)+2,v=pow(x,u,n);
		if(v==1||v==n-1)
			continue;
		reg int j;
		for(j=0;j<t;++j){
			v=mul(v,v,n);
			if(v==n-1)
				break;
		}
		if(j>=t)
			return false;
	}
	return true;
}

int main(void){
	srand((ull)time(0));
	read();
	int m=read();
	while(m--){
		ll n=read();
		puts(Miller_Rabin(n)?"Yes":"No");
	}
	return 0;
}
