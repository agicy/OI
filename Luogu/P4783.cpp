#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=400;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

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

int n;
int a[MAXN][MAXN<<1];

int main(void){
	n=read();
	for(reg int i=0;i<n;++i){
		a[i][i+n]=1;
		for(reg int j=0;j<n;++j)
			a[i][j]=read();
	}
	for(reg int i=0;i<n;++i){
		reg int ptr=-1;
		for(reg int j=i;j<n;++j)
			if(a[j][i]){
				ptr=j;
				break;
			}
		if(ptr==-1){
			writeln("No Solution");
			flush();
			return 0;
		}
		for(reg int j=0;j<(n<<1);++j)
			swap(a[ptr][j],a[i][j]);
		reg int inv=fpow(a[i][i],mod-2);
		for(reg int j=i;j<(n<<1);++j)
			a[i][j]=1ll*a[i][j]*inv%mod;
		for(reg int j=0;j<n;++j)
			if(i!=j&&a[j][i]){
				reg int d=a[j][i];
				for(reg int k=i;k<(n<<1);++k)
					a[j][k]=sub(a[j][k],1ll*a[i][k]*d%mod);
			}
	}
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			write(a[i][j+n]),putchar(j==n-1?'\n':' ');
	flush();
	return 0;
}