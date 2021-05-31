#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=17;

inline void solve(reg int x,reg int a,reg int ans[]){
	if(!x)
		ans[0]=0;
	else if(x==1)
		ans[0]=0,ans[1]=1;
	else{
		reg int val=1<<(x-1);
		if(a&val){
			solve(x-1,1,ans),solve(x-1,a^(val+1),ans+val);
			for(reg int i=val;i<(1<<x);++i)
				ans[i]=ans[i]^(val+1);
		}
		else{
			solve(x-1,a,ans),solve(x-1,ans[1],ans+val);
			for(reg int i=val;i<(1<<x);++i)
				ans[i]=ans[i]^val;
			static int tmp[1<<MAXN];
			tmp[0]=ans[0];
			for(reg int i=0;i<val;++i)
				tmp[i+1]=ans[i+val];
			for(reg int i=val+1;i<(1<<x);++i)
				tmp[i]=ans[i-val];
			for(reg int i=0;i<(1<<x);++i)
				ans[i]=tmp[i];
		}
	}
	return;
}

int n,A,B;
int ans[1<<MAXN];

int main(void){
	scanf("%d%d%d",&n,&A,&B);
	B^=A;
	if(__builtin_parity(B)){
		writeln("YES");
		solve(n,B,ans);
		reg int U=(1<<n)-1;
		for(reg int i=0;i<=U;++i)
			write(ans[i]^A),putchar(i==U?'\n':' ');
	}
	else
		writeln("NO");
	flush();
	return 0;
}