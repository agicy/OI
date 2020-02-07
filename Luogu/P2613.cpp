#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 19260817
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar(),res%=MOD;
	return f?-res:res;
}

ll a,b;

inline void exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(!b){
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
	return;
}

int main(void){
	a=read(),b=read();
	if(b==0)
		puts("Angry!");
	else{
		ll x,y;
		exgcd(b,MOD,x,y);
		reg ll inv=(x%MOD+MOD)%MOD;
		printf("%lld\n",a*inv%MOD);
	}
	return 0;
}
