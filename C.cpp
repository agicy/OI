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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e6+5;
const int MAXM=5e5+5;

int n,k,m;
char s[MAXN];
int l[MAXM],r[MAXM];

namespace Subtask2{
	bool tmp[MAXN];
	bool rev[MAXN];
	inline void Solve(void){
		for(reg int j=1;j<=n;++j)
			tmp[j]=s[j]-'0';
		for(reg int i=1;i<=m;++i){
			reg int ans=0;
			reg bool sum=false;
			for(reg int j=l[i];j+k-1<=r[i];++j){
				sum^=rev[j];
				if(tmp[j]^sum){
					rev[j]^=1,sum^=1,rev[j+k]^=1;
					++ans;
				}
			}
			reg bool flag=true;
			for(reg int j=max(r[i]-k+2,l[i]);j<=r[i];++j){
				sum^=rev[j];
				if(tmp[j]^sum){
					flag=false;
					break;
				}
			}
			if(flag)
				writeln(ans);
			else
				writeln(-1);
			for(reg int j=l[i];j<=r[i]+1;++j)
				rev[j]=false;
		}
		return;
	}
}

namespace Subtask{
	bool tmp[MAXN];
	bool rev[MAXN];
	inline void Solve(void){
		for(reg int j=1;j<=n;++j)
			tmp[j]=s[j]-'0';
		for(reg int i=1;i<=m;++i){
			reg int ans=0;
			reg bool sum=false;
			for(reg int j=l[i];j+k-1<=r[i];++j){
				sum^=rev[j];
				if(tmp[j]^sum){
					rev[j]^=1,sum^=1,rev[j+k]^=1;
					++ans;
				}
			}
			reg bool flag=true;
			for(reg int j=max(r[i]-k+2,l[i]);j<=r[i];++j){
				sum^=rev[j];
				if(tmp[j]^sum){
					flag=false;
					break;
				}
			}
			if(flag)
				writeln(ans);
			else
				writeln(-1);
			for(reg int j=l[i];j<=r[i]+1;++j)
				rev[j]=false;
		}
		return;
	}
}

int main(void){
	n=read(),k=read(),m=read();
	read(s+1);
	for(reg int i=1;i<=m;++i)
		l[i]=read(),r[i]=read();
	if(n<=5e3&&m<=5e3)
		Subtask2::Solve();
	else
		Subtask::Solve();
	flush();
	return 0;
}