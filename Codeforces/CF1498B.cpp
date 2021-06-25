#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(lg) (wp1==wp2&&(flush(),0),wbuf[wp1++]=lg)
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

const int lim=20;

int n,w;
int T[lim];
map<int,int> lg;

int main(void){
	for(reg int i=0;i<lim;++i)
		lg[1<<i]=i;
	reg int t=read();
	while(t--){
		n=read(),w=read();
		fill(T,T+lim,0);
		for(reg int i=1;i<=n;++i)
			++T[lg[read()]];
		reg int ans=0;
		while(true){
			++ans;
			reg int sum=w;
			for(reg int i=lim-1;i>=0;--i){
				reg int cnt=min(sum/(1<<i),T[i]);
				T[i]-=cnt,sum-=(cnt<<i);
			}
			reg bool flag=true;
			for(reg int i=0;i<lim&&flag;++i)
				if(T[i])
					flag=false;
			if(flag)
				break;
		}
		writeln(ans);
	}
	flush();
	return 0;
}