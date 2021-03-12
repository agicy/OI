#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

namespace Poly{
	const int p=998244353;
	typedef vector<int> poly;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%p;
			x=1ll*x*x%p;
			exp>>=1;
		}
		return res;
	}
	inline void FWT_xor(poly& a,reg int flag){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k){
					reg int x=a[j+k],y=a[i+j+k];
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
		if(flag==-1){
			reg int inv=fpow(n,p-2);
			for(reg int i=0;i<n;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
}

using namespace Poly;

int main(void){
	reg int n=read(),S=(1<<n);
	poly a;
	a.resize(S);
	reg int sum=0;
	for(reg int i=0;i<S;++i){
		a[i]=read();
		sum=add(sum,a[i]);
	}
	sum=fpow(sum,p-2);
	for(reg int i=0;i<S;++i)
		a[i]=1ll*a[i]*sum%p;
	FWT_xor(a,1),a[0]=0;
	for(reg int i=1;i<S;++i){
		a[i]=1ll*S*fpow(sub(a[i],1),p-2)%p;
		a[0]=sub(a[0],a[i]);
	}
	FWT_xor(a,-1);
	for(reg int i=0;i<S;++i)
		writeln(a[i]);
	flush();
	return 0;
}