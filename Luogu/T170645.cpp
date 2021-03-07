#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

inline uint readu(void){
	reg char ch=getchar();
	reg uint res=0;
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e4+5;

uint seed;

inline uint xorshift32(void){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}

int A[MAXN];
int sum[MAXN];

int main(void){
	reg int T=read();
	while(T--){
		reg int n;
		n=read(),seed=readu();
		reg int ans=0;
		for(reg int i=0;i<n;++i)
			A[i]=xorshift32()>>16&1;
		fill(sum,sum+n,0);
		reg int top=0;
		static int S[MAXN];
		for(reg int i=0;i<n;++i)
			if(!A[i]&&top)
				++sum[S[top--]],--sum[i+1],++ans;
			else if(A[i])
				S[++top]=i;
		reg int Max=sum[0];
		for(reg int i=1;i<n;++i)
			Max=max(Max,sum[i]+=sum[i-1]);
		writeln(min(ans/2,ans-Max));
	}
	flush();
	return 0;
}