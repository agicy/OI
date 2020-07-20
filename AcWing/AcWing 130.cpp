#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=60000+5;
const int MAXSIZE=60000+5;
const ll BASE=1000000000;
const int LGBASE=9;

struct BigNumber{
	int len;
	ll unit[MAXSIZE];
	inline BigNumber(void){
		len=0;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline BigNumber(reg ll n){
		len=0;
		memset(unit,0,sizeof(unit));
		unit[0]=n;
		return;
	}
	inline void Mul(reg ll n){
		for(reg int i=0;i<=len;++i){
			unit[i]*=n;
		}
		for(reg int i=0;i<=len;++i){
			unit[i+1]+=unit[i]/BASE;
			unit[i]%=BASE;
		}
		while(unit[len+1])
			++len;
		return;
	}
	inline void Print(void){
		printf("%lld",unit[len]);
		for(reg int i=len-1;i>=0;--i)
			printf("%0*lld",LGBASE,unit[i]);
		putchar('\n');
		return;
	}
};

int n;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	return;
}

int cnt[MAXN<<1];

inline void Div(reg int n,reg int flag){
	for(reg int i=2;i*i<=n&&n!=1;++i)
		while(n%i==0){
			cnt[i]+=flag;
			n/=i;
		}
	if(n!=1)
		cnt[n]+=flag;
	return;
}

inline void Work(void){
	BigNumber res=1;
	for(reg int i=n+2;i<=n*2;++i)
		Div(i,+1);
	for(reg int i=1;i<=n;++i)
		Div(i,-1);
	for(reg int i=2;i<=2*n;++i)
		while(cnt[i]){
			res.Mul(i);
			--cnt[i];
		}
	res.Print();
	return;
}
