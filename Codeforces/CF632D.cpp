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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e6+5;
const int MAXM=1e6+5;

int n,m;
int a[MAXN];
int T[MAXM];
int cnt[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]<=m)
			++T[a[i]];
	}
	for(reg int i=1;i<=m;++i)
		if(T[i])
			for(reg int j=i;j<=m;j+=i)
				cnt[j]+=T[i];
	reg int ans1=1,ans2=0;
	for(reg int i=1;i<=m;++i)
		if(ans2<cnt[i])
			ans1=i,ans2=cnt[i];
	write(ans1),putchar(' '),write(ans2),putchar('\n');
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		if(!(ans1%a[i]))
			write(i),putchar(++tot==ans2?'\n':' ');
	flush();
	return 0;
}